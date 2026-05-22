#include <iostream>
#include <string>
#include <limits>

using namespace std;

class ToDoList {
private:
    static const int MAX_TASKS = 100;
    string tasks[MAX_TASKS];
    int taskCount;

public:
    ToDoList() : taskCount(0) {}

    bool addTask(const string& task) {
        if (taskCount < MAX_TASKS) {
            tasks[taskCount++] = task;
            return true;
        }
        return false;
    }

    bool removeTask(const string& task) {
        for (int i = 0; i < taskCount; ++i) {
            if (tasks[i] == task) {
                for (int j = i; j < taskCount - 1; ++j) {
                    tasks[j] = tasks[j + 1];
                }
                --taskCount;
                return true;
            }
        }
        return false;
    }

    void displayTasks() const {
        for (int i = 0; i < taskCount; ++i) {
            cout << i + 1 << ". " << tasks[i] << endl;
        }
    }
};

int main() {
    system("clear");
    system(" chmod +x ./welcometodolist.sh");
    system("./welcometodolist.sh");


    ToDoList todoList;
    string input;
    int option;

    do {
        cout << "\nTo-Do List Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. Display Tasks\n";
        cout << "4. Exit\n";
        cout << "Enter your option: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option) {
            case 1:
                cout << "Enter task: ";
                getline(cin, input);
                if (todoList.addTask(input)) {
                    cout << "Task added successfully.\n";
                } else {
                    cout << "Error: Task list is full.\n";
                }
                break;

            case 2:
                cout << "Enter task to remove: ";
                getline(cin, input);
                if (todoList.removeTask(input)) {
                    cout << "Task removed successfully.\n";
                } else {
                    cout << "Error: Task not found.\n";
                }
                break;

            case 3:
                cout << "\nTo-Do List:\n";
                todoList.displayTasks();
                break;

            case 4:
                cout << "Exiting the application.\n";
	system("./dealloc_resource TODO");
                break;

            default:
                cout << "Invalid option. Please try again.\n";
        }

    } while (option != 4);

    return 0;
}
