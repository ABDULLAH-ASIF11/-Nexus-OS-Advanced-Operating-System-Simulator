#include "ready_queue.h"

ReadyQueue::ReadyQueue() { pthread_mutex_init(&mutex_, nullptr); }
ReadyQueue::~ReadyQueue() { pthread_mutex_destroy(&mutex_); }

void ReadyQueue::push(int pcbId, int level) {
  pthread_mutex_lock(&mutex_);
  if (level == 1) {
    foreground_.push_back(pcbId);
  } else {
    background_.push_back(pcbId);
  }
  pthread_mutex_unlock(&mutex_);
}

bool ReadyQueue::popForeground(int* pcbId) {
  pthread_mutex_lock(&mutex_);
  if (foreground_.empty()) {
    pthread_mutex_unlock(&mutex_);
    return false;
  }
  *pcbId = foreground_.front();
  foreground_.pop_front();
  pthread_mutex_unlock(&mutex_);
  return true;
}

bool ReadyQueue::popBackground(int* pcbId) {
  pthread_mutex_lock(&mutex_);
  if (background_.empty()) {
    pthread_mutex_unlock(&mutex_);
    return false;
  }
  *pcbId = background_.front();
  background_.pop_front();
  pthread_mutex_unlock(&mutex_);
  return true;
}

bool ReadyQueue::empty() const {
  pthread_mutex_lock(&mutex_);
  bool v = foreground_.empty() && background_.empty();
  pthread_mutex_unlock(&mutex_);
  return v;
}
