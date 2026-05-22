#include <filesystem>
#include <iostream>
#include <string>

int main() {
  std::string path;
  std::cout << "File to delete: ";
  std::getline(std::cin, path);
  std::filesystem::remove(path);
  std::cout << "Deleted.\n";
  return 0;
}
