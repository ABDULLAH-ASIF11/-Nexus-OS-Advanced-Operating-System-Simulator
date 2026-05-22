#include <filesystem>
#include <iostream>
#include <string>

int main() {
  std::string src, dst;
  std::cout << "Source file: ";
  std::getline(std::cin, src);
  std::cout << "Destination file: ";
  std::getline(std::cin, dst);
  std::filesystem::copy_file(src, dst, std::filesystem::copy_options::overwrite_existing);
  std::cout << "Copied.\n";
  return 0;
}
