#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string path;
  std::cout << "File to edit: ";
  std::getline(std::cin, path);
  std::ifstream in(path);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(in, line)) lines.push_back(line);
  for (size_t i = 0; i < lines.size(); ++i) std::cout << i + 1 << ": " << lines[i] << "\n";
  int idx;
  std::cout << "Line number to replace: ";
  std::cin >> idx;
  std::cin.ignore();
  std::cout << "New content: ";
  std::getline(std::cin, line);
  if (idx > 0 && idx <= static_cast<int>(lines.size())) lines[idx - 1] = line;
  std::ofstream out(path);
  for (const auto& l : lines) out << l << "\n";
  return 0;
}
