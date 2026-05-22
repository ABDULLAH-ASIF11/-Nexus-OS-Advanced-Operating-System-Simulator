#include <filesystem>
#include <iostream>
#include <string>

int main() {
  std::string src, dst;
  std::cout << "Source file: ";
  std::getline(std::cin, src);
  std::cout << "Destination file: ";
  std::getline(std::cin, dst);
  std::filesystem::rename(src, dst);
  std::cout << "Moved.\n";
  return 0;
}
