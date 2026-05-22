#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
  std::srand(std::time(nullptr));
  int target = 1 + std::rand() % 100;
  std::cout << "Guess a number (1-100):\n";
  while (true) {
    int x;
    std::cin >> x;
    if (x == target) break;
    std::cout << (x < target ? "Higher\n" : "Lower\n");
  }
  std::cout << "You win!\n";
  return 0;
}
