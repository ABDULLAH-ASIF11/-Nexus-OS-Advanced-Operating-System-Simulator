#include <cstdlib>

int main() { return system("ps -eo pid,ppid,stat,comm --sort=pid | head -n 25"); }
