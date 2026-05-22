#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctime>
#include <cstring>
#include <cstdlib>

using namespace std;
long int ram;
long int need;
int main(int argc, char* argv[])
{
    ram=stol(argv[2]);
    need=stol(argv[3]);
    if(need<=ram){
  setenv("MINIOS_EXE", argv[1], 1);
  system("chmod +x ./launch_app.sh 2>/dev/null");
  system("bash ./launch_app.sh");
}
else{
      system("notify-send 'NOT ENOUGH RESOURCES'");
}
  return 0;
}

