#include <filesystem>
#include <iostream>
#include <string>

int main() {
  std::string src, dst;
  std::cout << "Source folder: ";
  std::getline(std::cin, src);
  std::cout << "Backup folder: ";
  std::getline(std::cin, dst);
  std::filesystem::create_directories(dst);
  for (const auto& e : std::filesystem::directory_iterator(src)) {
    if (std::filesystem::is_regular_file(e.path())) {
      std::filesystem::copy_file(e.path(), std::filesystem::path(dst) / e.path().filename(),
                                 std::filesystem::copy_options::overwrite_existing);
    }
  }
  std::cout << "Backup complete.\n";
  return 0;
}
