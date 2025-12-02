#include <iostream>
#include <vector>
using namespace std;

struct Task {
    string description;
    bool is_completed;

    Task(const string& desc, bool is_compltd = false) {
        description = desc;
        is_completed = is_compltd;
    }
};

int main() {
    string input;
    vector<Task> tasks;
    tasks.push_back(Task("Buy a bread", false));
    tasks.push_back(Task("Do homework", true));
    tasks.push_back(Task("Learn C#", false));
    cout << "\n====C++ TODO MANAGER====" << endl;
    cout << "Commands: list, help, exit" << endl;

    while (true) {
        cout << "> ";
        getline(cin, input);

        if (input.empty()) {
            continue;
        } else if (input == "list") {
            for (int i = 0; i < tasks.size(); i++) {
                cout << i + 1 << ". " << tasks[i].description << " -- " << (tasks[i].is_completed ? "Yes" : "No") << endl;
            }
        } else if (input == "exit") {
            break;
        } else if (input == "help") {
            cout << "Available commands:\n";
            cout << "  list - Show all tasks\n";
            cout << "  help - Show this help\n";
            cout << "  exit - Quit program\n";
        } else {
            cout << "Invalid command!" << endl;
        }

        cout << endl;
    }

    return 0;
}