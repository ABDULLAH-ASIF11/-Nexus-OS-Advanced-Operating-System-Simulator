#include <iostream>
#include <unistd.h>

int main() {
  int secs = 5;
  std::cout << "Duration (seconds): ";
  std::cin >> secs;
  for (int i = 0; i < secs; ++i) {
    std::cout << '\a' << "beep\n";
    usleep(900000);
  }
  return 0;
}
