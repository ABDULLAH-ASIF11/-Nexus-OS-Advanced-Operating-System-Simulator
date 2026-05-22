#include <iostream>
#include <unistd.h>

int main() {
  int n;
  std::cout << "Countdown seconds: ";
  std::cin >> n;
  for (int i = n; i >= 0; --i) {
    std::cout << i << "\n";
    sleep(1);
  }
  std::cout << '\a' << "Time up!\n";
  return 0;
}
