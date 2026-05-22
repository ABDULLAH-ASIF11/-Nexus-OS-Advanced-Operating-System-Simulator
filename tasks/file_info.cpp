#include <filesystem>
#include <iostream>
#include <string>

int main() {
  std::string path;
  std::cout << "Path: ";
  std::getline(std::cin, path);
  auto st = std::filesystem::status(path);
  std::cout << "Size: " << std::filesystem::file_size(path) << " bytes\n";
  std::cout << "Permissions: " << static_cast<unsigned>(st.permissions()) << "\n";
  return 0;
}
