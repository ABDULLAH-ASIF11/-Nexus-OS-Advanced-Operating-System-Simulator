#include <ctime>
#include <iostream>
#include <unistd.h>

int main() {
  for (int i = 0; i < 30; ++i) {
    std::time_t now = std::time(nullptr);
    std::cout << std::ctime(&now);
    usleep(1000000);
  }
  return 0;
}
