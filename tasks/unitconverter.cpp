#include <iostream>
using namespace std;

int main() {
    system("clear");
    system(" chmod +x ./welcomeunitconverter.sh");
    system("./welcomeunitconverter.sh");
    double input_value;
    int choice;

    // Display the menu
    cout << "Please select an option:" << endl;
    cout << "1. Inches to Centimeters" << endl;
    cout << "2. Feet to Meters" << endl;
    cout << "3. Yards to Meters" << endl;
    cout << "4. Miles to Kilometers" << endl;
    cout << "Enter your choice (1-4): ";
    cin >> choice;

    // Get the input value
    cout << "Enter the value to convert: ";
    cin >> input_value;

    // Convert the value based on the user's choice
    switch (choice) {
        case 1:
            cout << input_value << " inches is equal to " << input_value * 2.54 << " centimeters." << endl;
            break;
        case 2:
            cout << input_value << " feet is equal to " << input_value * 0.3048 << " meters." << endl;
            break;
        case 3:
            cout << input_value << " yards is equal to " << input_value * 0.9144 << " meters." << endl;
            break;
        case 4:
            cout << input_value << " miles is equal to " << input_value * 1.60934 << " kilometers." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
    cin.ignore();
cout <<"\t\t\t" << "Press any key to Exit..." << endl;
  cin.get();
  system("./dealloc_resource UNITCONVERT");

    return 0;
}
