#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

int main() {
  int n = 10;
  std::cout << "How many random numbers? ";
  std::cin >> n;
  std::ofstream out("random_numbers.txt");
  std::srand(std::time(nullptr));
  for (int i = 0; i < n; ++i) out << (std::rand() % 1000) << "\n";
  std::cout << "Saved random numbers.\n";
  return 0;
}
