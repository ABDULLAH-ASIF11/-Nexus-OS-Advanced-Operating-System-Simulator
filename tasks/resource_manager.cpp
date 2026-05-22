#include "resource_manager.h"

ResourceManager::ResourceManager(int totalRamMB, int totalHddMB, int totalCores)
    : totalRamMB_(totalRamMB),
      totalHddMB_(totalHddMB),
      totalCores_(totalCores),
      usedRamMB_(0),
      usedHddMB_(0),
      usedCores_(0) {
  pthread_mutex_init(&mutex_, nullptr);
  pthread_cond_init(&cond_, nullptr);
  sem_init(&ramSem_, 0, totalRamMB_ > 0 ? totalRamMB_ : 1);
  sem_init(&hddSem_, 0, totalHddMB_ > 0 ? totalHddMB_ : 1);
}

ResourceManager::~ResourceManager() {
  sem_destroy(&ramSem_);
  sem_destroy(&hddSem_);
  pthread_cond_destroy(&cond_);
  pthread_mutex_destroy(&mutex_);
}

bool ResourceManager::requestResources(int ramMB, int hddMB) {
  pthread_mutex_lock(&mutex_);
  bool ok = (usedRamMB_ + ramMB <= totalRamMB_) && (usedHddMB_ + hddMB <= totalHddMB_);
  if (ok) {
    usedRamMB_ += ramMB;
    usedHddMB_ += hddMB;
  }
  pthread_mutex_unlock(&mutex_);
  return ok;
}

void ResourceManager::releaseResources(int ramMB, int hddMB) {
  pthread_mutex_lock(&mutex_);
  usedRamMB_ -= ramMB;
  usedHddMB_ -= hddMB;
  if (usedRamMB_ < 0) usedRamMB_ = 0;
  if (usedHddMB_ < 0) usedHddMB_ = 0;
  pthread_cond_broadcast(&cond_);
  pthread_mutex_unlock(&mutex_);
}

int ResourceManager::freeRamMB() const {
  pthread_mutex_lock(&mutex_);
  int v = totalRamMB_ - usedRamMB_;
  pthread_mutex_unlock(&mutex_);
  return v;
}

int ResourceManager::freeHddMB() const {
  pthread_mutex_lock(&mutex_);
  int v = totalHddMB_ - usedHddMB_;
  pthread_mutex_unlock(&mutex_);
  return v;
}

int ResourceManager::usedCores() const {
  pthread_mutex_lock(&mutex_);
  int v = usedCores_;
  pthread_mutex_unlock(&mutex_);
  return v;
}

int ResourceManager::totalCores() const { return totalCores_; }

bool ResourceManager::tryAcquireCore() {
  pthread_mutex_lock(&mutex_);
  if (usedCores_ >= totalCores_) {
    pthread_mutex_unlock(&mutex_);
    return false;
  }
  ++usedCores_;
  pthread_mutex_unlock(&mutex_);
  return true;
}

void ResourceManager::releaseCore() {
  pthread_mutex_lock(&mutex_);
  --usedCores_;
  if (usedCores_ < 0) usedCores_ = 0;
  pthread_cond_broadcast(&cond_);
  pthread_mutex_unlock(&mutex_);
}
