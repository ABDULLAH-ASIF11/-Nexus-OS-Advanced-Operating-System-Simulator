#include <ctime>
#include <fstream>
#include <iostream>

int main() {
  std::ofstream out("os_logs.txt", std::ios::app);
  std::time_t now = std::time(nullptr);
  out << "Log entry at " << std::ctime(&now);
  std::cout << "Log appended.\n";
  return 0;
}
