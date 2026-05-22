#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::string name;
  std::cout << "File name: ";
  std::getline(std::cin, name);
  std::ofstream out(name);
  std::cout << "Created.\n";
  return 0;
}
