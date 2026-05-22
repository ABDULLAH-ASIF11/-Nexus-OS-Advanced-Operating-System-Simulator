#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "kernel.h"
#include "resource_manager.h"
#include "scheduler.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

static const string kDefaultOsName = "NebulaOS";

void bootAnimation(const string& osName) {
  system("clear");
  cout << "Booting " << osName << "...\n";
  cout << "[";
  for (int i = 0; i < 30; ++i) {
    cout << "#";
    cout.flush();
    usleep(90000);
  }
  cout << "]\n";
  cout << "Welcome to " << osName << "!\n";
}

void printResources(const ResourceManager& rm, int totalRamMB, int totalHddMB) {
  int usedRam = totalRamMB - rm.freeRamMB();
  int usedHdd = totalHddMB - rm.freeHddMB();
  cout << "RAM: " << usedRam << "/" << totalRamMB << " MB | HDD: " << usedHdd << "/" << totalHddMB
       << " MB | Cores: " << rm.usedCores() << "/" << rm.totalCores() << "\n";
}

int main(int argc, char* argv[]) {
  if (argc < 4) {
    cout << "Usage: ./OS <RAM_GB> <HDD_GB> <CORES> [OS_NAME]\n";
    return 1;
  }

  int ramGb = std::atoi(argv[1]);
  int hddGb = std::atoi(argv[2]);
  int cores = std::atoi(argv[3]);
  string osName = argc >= 5 ? argv[4] : kDefaultOsName;
  if (ramGb <= 0 || hddGb <= 0 || cores <= 0) {
    cout << "Invalid resources. All must be > 0\n";
    return 1;
  }

  int totalRamMB = ramGb * 1024;
  int totalHddMB = hddGb * 1024;
  bootAnimation(osName);

  ResourceManager resourceManager(totalRamMB, totalHddMB, cores);
  Scheduler scheduler(&resourceManager, 5000);
  Kernel kernel(&scheduler);

  std::map<int, TaskSpec> tasks = {
      {1, {1, "Calculator", "./tasks/calculator", 1, 128, 40, 30000, 1}},
      {2, {2, "Notepad", "./tasks/notepad", 1, 256, 80, 50000, 1}},
      {3, {3, "Text Search", "./tasks/text_search", 1, 128, 60, 25000, 2}},
      {4, {4, "File Editor", "./tasks/file_editor", 1, 128, 80, 30000, 2}},
      {5, {5, "Mini Game", "./tasks/mini_game", 1, 128, 30, 30000, 2}},
      {6, {6, "File Copy", "./tasks/file_copy", 2, 64, 120, 12000, 3}},
      {7, {7, "File Move", "./tasks/file_move", 2, 64, 120, 12000, 3}},
      {8, {8, "File Delete", "./tasks/file_delete", 2, 64, 80, 10000, 3}},
      {9, {9, "Print Simulation", "./tasks/print_sim", 2, 64, 20, 10000, 3}},
      {10, {10, "Music Simulation", "./tasks/music_sim", 2, 64, 20, 10000, 3}},
      {11, {11, "Clock", "./tasks/clock", 2, 64, 20, 120000, 1}},
      {12, {12, "Calendar", "./tasks/calendar", 2, 64, 20, 120000, 1}},
      {13, {13, "File Creator", "./tasks/file_creator", 1, 64, 40, 15000, 2}},
      {14, {14, "File Info", "./tasks/file_info", 1, 64, 20, 15000, 2}},
      {15, {15, "RAM Viewer", "./tasks/ram_viewer", 2, 64, 20, 10000, 3}},
      {16, {16, "Process Viewer", "./tasks/process_viewer", 2, 64, 20, 10000, 3}},
      {17, {17, "Log Generator", "./tasks/log_generator", 2, 64, 40, 10000, 3}},
      {18, {18, "Random Generator", "./tasks/rand_gen", 2, 64, 40, 10000, 3}},
      {19, {19, "Timer/Alarm", "./tasks/timer_alarm", 1, 64, 20, 15000, 2}},
      {20, {20, "Auto Backup", "./tasks/auto_backup", 2, 96, 200, 30000, 3}},
  };

  // Auto-start clock and calendar after boot.
  scheduler.enqueueTask(tasks[11]);
  scheduler.enqueueTask(tasks[12]);

  bool running = true;
  while (running) {
    scheduler.tick();
    cout << "\n================ " << osName << " ================\n";
    printResources(resourceManager, totalRamMB, totalHddMB);
    cout << "Mode: " << (kernel.isKernelMode() ? "Kernel" : "User") << "\n";
    scheduler.showQueue();
    cout << "\nTasks Menu (1-20), 30=Minimize, 31=Resume, 40=Kernel Login, 41=Kernel Logout,\n";
    cout << "42=Force Kill (kernel), 43=Show All PCBs (kernel), 99=Show PCBs, 0=Shutdown\n";
    cout << "Enter choice: ";
    int choice = -1;
    cin >> choice;

    if (choice == 0) {
      running = false;
    } else if (choice >= 1 && choice <= 20) {
      int pcbId = scheduler.enqueueTask(tasks[choice]);
      cout << "Task queued with PCB ID: " << pcbId << "\n";
    } else if (choice == 30) {
      int id;
      cout << "Enter PCB ID to minimize: ";
      cin >> id;
      scheduler.minimizeProcess(id);
    } else if (choice == 31) {
      int id;
      cout << "Enter PCB ID to resume: ";
      cin >> id;
      scheduler.resumeProcess(id);
    } else if (choice == 40) {
      string pwd;
      cout << "Kernel password: ";
      cin >> pwd;
      cout << (kernel.enterKernelMode(pwd) ? "Kernel mode enabled\n" : "Wrong password\n");
    } else if (choice == 41) {
      kernel.exitKernelMode();
      cout << "Back to user mode\n";
    } else if (choice == 42) {
      if (!kernel.isKernelMode()) {
        cout << "Enter kernel mode first.\n";
      } else {
        int id;
        cout << "PCB ID to force kill: ";
        cin >> id;
        kernel.forceKill(id);
      }
    } else if (choice == 43) {
      if (!kernel.isKernelMode()) {
        cout << "Enter kernel mode first.\n";
      } else {
        kernel.showAllPcbs();
      }
    } else if (choice == 99) {
      scheduler.showPcbs();
    } else {
      cout << "Invalid choice\n";
    }
  }

  auto pcbs = scheduler.allPcbs();
  for (const auto& pcb : pcbs) {
    if (pcb.state != ProcessState::Terminated) {
      scheduler.killProcess(pcb.id);
    }
  }
  cout << "Goodbye from " << osName << "!\n";
  return 0;
}
