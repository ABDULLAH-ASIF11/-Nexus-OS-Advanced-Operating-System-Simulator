 #include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    system("clear");
system(" chmod +x ./welcomecalender.sh");
system("./welcomecalender.sh");
    for (int i = 1; i <= 12; i++) {
        cout << "Calendar for Month " << i << endl;
        system(("cal " + to_string(i) + " `date +\"%Y\"`").c_str());
    }
    cin.ignore();
    cout <<"\t\t\t" << "Press any key to Exit..." << endl;
  cin.get();
    system("./dealloc_resource CALENDER");
    return 0;
}

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 