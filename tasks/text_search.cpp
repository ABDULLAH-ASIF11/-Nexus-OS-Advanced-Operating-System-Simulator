#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string path, key, line;
  std::cout << "File path: ";
  std::getline(std::cin, path);
  std::cout << "Keyword: ";
  std::getline(std::cin, key);
  std::ifstream in(path);
  if (!in) return 1;
  int n = 0;
  while (std::getline(in, line)) {
    if (line.find(key) != std::string::npos) {
      std::cout << line << "\n";
      ++n;
    }
  }
  std::cout << "Matches: " << n << "\n";
  return 0;
}
