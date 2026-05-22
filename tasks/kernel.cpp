#include "kernel.h"

#include <iostream>

Kernel::Kernel(Scheduler* scheduler) : scheduler_(scheduler), kernelMode_(false) {}

bool Kernel::enterKernelMode(const std::string& password) {
  if (password == "minios123") {
    kernelMode_ = true;
    return true;
  }
  return false;
}

void Kernel::exitKernelMode() { kernelMode_ = false; }

bool Kernel::isKernelMode() const { return kernelMode_; }

void Kernel::forceKill(int pcbId) { scheduler_->killProcess(pcbId); }

void Kernel::showAllPcbs() const { scheduler_->showPcbs(); }
