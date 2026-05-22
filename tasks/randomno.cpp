#include <iostream>
#include <cstdlib> 
#include <ctime> 

using namespace std;

int main() {
    system("clear");
    system(" chmod +x ./welcomerandom.sh");
    system("./welcomerandom.sh");
    int range_start, range_end;
    
    cout << "Enter range start: ";
    cin >> range_start;
    
    cout << "Enter range end: ";
    cin >> range_end;
    
  
    srand(time(0));
    

    int random_num = rand() % (range_end - range_start + 1) + range_start;
    
  
    cout << "Random number within the range " << range_start << " to " << range_end << " is: " << random_num << endl;
    cin.ignore();
    cout <<"\t\t\t" << "Press any key to Exit..." << endl;
  cin.get();
  system("./dealloc_resource RANDOMNO");
    
    return 0;
}
