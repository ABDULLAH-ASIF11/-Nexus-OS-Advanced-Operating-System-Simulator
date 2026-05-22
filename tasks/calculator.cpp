# include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    int op;
    float num1, num2; 
    int loop;
    system("clear");
    system(" chmod +x ./welcomecalculator.sh");
    system("./welcomecalculator.sh");
    
    do
		  {
		   system("clear");
		  cout << "\t\t\tEnter Number 1: ";
		  cin >> num1;
		  cout << "\t\t\tEnter Number 2: ";
		  cin >> num2;
		  do
		  {
		      cout << "\t\t\tSelect Operator: " << endl;
		      cout << "\t\t\t1. Addition (+)" << endl
		          << "\t\t\t2. Subtraction (-)" << endl
		          << "\t\t\t3. Multiplication (*)" << endl
		          << "\t\t\t4. Division (/)" << endl
		          << "\t\t\tChoice: ";
		      cin >> op;
		      switch (op)
		      {
		      case 1:
		          cout <<"\t\t\t" <<num1 << " + " << num2 << " = " << num1 + num2;
		          break;

		      case 2:
		          cout <<"\t\t\t"<< num1 << " - " << num2 << " = " << num1 - num2;
		          break;

		      case 3:
		          cout <<"\t\t\t"<< num1 << " * " << num2 << " = " << num1 * num2;
		          break;

		      case 4:
		      	  if (num2==0)
		          {
		              system("zenity --warning --width=500 --height=200 --text 'Divide by zero Interrupt'");
		              break;
		          }
		          cout <<"\t\t\t"<< num1 << " / " << num2 << " = " << num1 / num2;
		          break;

		      default:
		          cout <<"\t\t\t"<< "Wrong Operator Please Try Again";
		          usleep(500);
		          break;
		      }
		      cout << endl;
		  }while (op < 1 || op > 4);
		  cout <<"\t\t" << "Do you want another calculation: (1/0) ";
		  cin >> loop;
    }while(loop);
		cin.ignore();
		cout <<"\t\t\t" << "Press any key to Exit..." << endl;
		cin.get();
    system("./dealloc_resource CALCULATOR");
    return 0;
}
