#include <iostream>

int main() {
  double a, b;
  char op;
  std::cout << "Calculator: enter <num1 op num2> (e.g. 2 + 3): ";
  std::cin >> a >> op >> b;
  if (op == '+') std::cout << (a + b) << "\n";
  if (op == '-') std::cout << (a - b) << "\n";
  if (op == '*') std::cout << (a * b) << "\n";
  if (op == '/' && b != 0) std::cout << (a / b) << "\n";
  std::cout << "Calculator done.\n";
  return 0;
}
