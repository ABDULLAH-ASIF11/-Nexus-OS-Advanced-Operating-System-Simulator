#include "process.h"

const char* stateToString(ProcessState state) {
  switch (state) {
    case ProcessState::Ready:
      return "Ready";
    case ProcessState::Running:
      return "Running";
    case ProcessState::Blocked:
      return "Blocked";
    case ProcessState::Terminated:
      return "Terminated";
  }
  return "Unknown";
}
