#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream in("/proc/meminfo");
  std::string line;
  int shown = 0;
  while (std::getline(in, line) && shown < 5) {
    std::cout << line << "\n";
    ++shown;
  }
  return 0;
}
