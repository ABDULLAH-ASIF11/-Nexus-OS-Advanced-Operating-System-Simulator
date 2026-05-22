#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

int main() {
  std::string path, line;
  std::cout << "File to print: ";
  std::getline(std::cin, path);
  std::ifstream in(path);
  while (std::getline(in, line)) {
    std::cout << line << "\n";
    usleep(250000);
  }
  return 0;
}
