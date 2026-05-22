#include "scheduler.h"

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include <chrono>
#include <cstring>
#include <iostream>

#include "ipc.h"

Scheduler::Scheduler(ResourceManager* rm, int rrQuantumMs)
    : rm_(rm), quantumMs_(rrQuantumMs), nextPcbId_(1) {}

long long Scheduler::nowMs() const {
  using namespace std::chrono;
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int Scheduler::enqueueTask(const TaskSpec& task) {
  ProcessControlBlock pcb;
  pcb.id = nextPcbId_++;
  pcb.name = task.name;
  pcb.ramMB = task.ramMB;
  pcb.hddMB = task.hddMB;
  pcb.burstMs = task.burstMs;
  pcb.priority = task.priority;
  pcb.queueLevel = task.queueLevel;
  pcb.state = ProcessState::Ready;
  pcbs_[pcb.id] = pcb;
  binaries_[pcb.id] = task.binaryPath;
  queue_.push(pcb.id, pcb.queueLevel);
  return pcb.id;
}

bool Scheduler::launch(ProcessControlBlock& pcb, const std::string& binaryPath) {
  int reqPipe[2];
  if (!createPipe(reqPipe)) return false;
  pid_t pid = fork();
  if (pid < 0) return false;

  if (pid == 0) {
    close(reqPipe[0]);
    ResourceRequest req{pcb.ramMB, pcb.hddMB};
    childSendRequest(reqPipe[1], req);
    close(reqPipe[1]);
    execlp("xterm", "xterm", "-e", binaryPath.c_str(), (char*)nullptr);
    _exit(1);
  }

  close(reqPipe[1]);
  ResourceRequest req{};
  bool got = parentReadRequest(reqPipe[0], &req);
  close(reqPipe[0]);
  if (!got || !rm_->requestResources(req.ramMB, req.hddMB) || !rm_->tryAcquireCore()) {
    kill(pid, SIGTERM);
    waitpid(pid, nullptr, 0);
    pcb.state = ProcessState::Terminated;
    return false;
  }
  pcb.pid = pid;
  pcb.state = ProcessState::Running;
  pcb.startedAtMs = nowMs();
  return true;
}

void Scheduler::tick() {
  // Collect terminated.
  for (auto& kv : pcbs_) {
    auto& pcb = kv.second;
    if (pcb.pid <= 0 || pcb.state == ProcessState::Terminated) continue;
    int status = 0;
    pid_t r = waitpid(pcb.pid, &status, WNOHANG);
    if (r == pcb.pid) {
      pcb.state = ProcessState::Terminated;
      rm_->releaseResources(pcb.ramMB, pcb.hddMB);
      rm_->releaseCore();
    }
  }

  // Time quantum for foreground.
  for (auto& kv : pcbs_) {
    auto& pcb = kv.second;
    if (pcb.state != ProcessState::Running || pcb.queueLevel != 1 || pcb.minimized) continue;
    if (nowMs() - pcb.startedAtMs > quantumMs_) {
      kill(pcb.pid, SIGSTOP);
      pcb.state = ProcessState::Blocked;
      queue_.push(pcb.id, 1);
      rm_->releaseCore();
    }
  }

  int id = -1;
  if (queue_.popForeground(&id) || queue_.popBackground(&id)) {
    auto& pcb = pcbs_[id];
    if (pcb.state == ProcessState::Terminated) return;
    if (pcb.pid > 0 && pcb.state == ProcessState::Blocked && !pcb.minimized) {
      if (rm_->tryAcquireCore()) {
        kill(pcb.pid, SIGCONT);
        pcb.state = ProcessState::Running;
        pcb.startedAtMs = nowMs();
      } else {
        queue_.push(pcb.id, pcb.queueLevel);
      }
      return;
    }
    launch(pcb, binaries_[id]);
  }
}

void Scheduler::showQueue() const {
  std::cout << "Ready Queue: foreground + background active\n";
}

void Scheduler::showPcbs() const {
  std::cout << "ID\tPID\tName\t\tState\tRAM\tHDD\tQ\n";
  for (const auto& kv : pcbs_) {
    const auto& pcb = kv.second;
    std::cout << pcb.id << "\t" << pcb.pid << "\t" << pcb.name << "\t\t" << stateToString(pcb.state)
              << "\t" << pcb.ramMB << "\t" << pcb.hddMB << "\t" << pcb.queueLevel << "\n";
  }
}

void Scheduler::minimizeProcess(int pcbId) {
  auto it = pcbs_.find(pcbId);
  if (it == pcbs_.end()) return;
  auto& pcb = it->second;
  pcb.minimized = true;
  if (pcb.state == ProcessState::Running) {
    kill(pcb.pid, SIGSTOP);
    pcb.state = ProcessState::Blocked;
    rm_->releaseCore();
  }
}

void Scheduler::resumeProcess(int pcbId) {
  auto it = pcbs_.find(pcbId);
  if (it == pcbs_.end()) return;
  auto& pcb = it->second;
  pcb.minimized = false;
  if (pcb.state == ProcessState::Blocked) queue_.push(pcb.id, pcb.queueLevel);
}

void Scheduler::killProcess(int pcbId) {
  auto it = pcbs_.find(pcbId);
  if (it == pcbs_.end()) return;
  auto& pcb = it->second;
  if (pcb.pid > 0 && pcb.state != ProcessState::Terminated) {
    kill(pcb.pid, SIGTERM);
    waitpid(pcb.pid, nullptr, 0);
  }
  pcb.state = ProcessState::Terminated;
  rm_->releaseResources(pcb.ramMB, pcb.hddMB);
  rm_->releaseCore();
}

std::vector<ProcessControlBlock> Scheduler::allPcbs() const {
  std::vector<ProcessControlBlock> out;
  for (const auto& kv : pcbs_) out.push_back(kv.second);
  return out;
}
