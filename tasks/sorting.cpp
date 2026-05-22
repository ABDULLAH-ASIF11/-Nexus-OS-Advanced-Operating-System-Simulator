#include <iostream>
#include <algorithm>

using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

int main() {
    system("clear");
    system(" chmod +x ./welcomesorting.sh");
    system("./welcomesorting.sh");
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[n];
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int choice;
    cout << "Enter 1 to sort in ascending order or 2 to sort in descending order: ";
    cin >> choice;
    switch (choice) {
        case 1:
            selectionSort(arr, n);
            cout << "Ascending order: ";
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            break;
        case 2:
            selectionSort(arr, n);
            reverse(arr, arr + n);
            cout << "Descending order: ";
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
    cin.ignore();
  cout <<"\t\t\t" << "Press any key to Exit..." << endl;
  cin.get();
  system("./dealloc_resource Sorting");
    return 0;
}
