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

void showHeader() {
    cout << "\n====C++ TODO MANAGER====" << endl;
    cout << "Commands: list, add, help, clear, exit" << endl;
}

void addTask(vector<Task>& tasks) {
    string taskDesc;

    cout << "Enter task description: ";
    getline(cin, taskDesc);

    tasks.push_back(Task(taskDesc, false));
    cout << "Task added!" << endl;
}

int main() {
    vector<Task> tasks;

    string input;
    tasks.push_back(Task("Buy a bread", false));
    tasks.push_back(Task("Do homework", true));
    tasks.push_back(Task("Learn C#", false));

    showHeader();

    while (true) {
        cout << "> ";
        getline(cin, input);

        if (input.empty()) {
            continue;
        } else if (input == "list") {
            for (int i = 0; i < tasks.size(); i++) {
                cout << i + 1 << ". " << tasks[i].description << " " <<
                (tasks[i].is_completed ? "[\033[32mDONE\033[0m]" : "[\033[31mNOT DONE\033[0m]") << endl;
            }
        } else if (input == "add") {
            addTask(tasks);
        } else if (input == "clear") {
            system("clear");
            showHeader();
        } else if (input == "help") {
            cout << "Available commands:\n";
            cout << "  list - Show all tasks\n";
            cout << "  add - Add a new task\n";
            cout << "  help - Show this help\n";
            cout << "  clear - Clear console\n";
            cout << "  exit - Quit program\n";
        } else if (input == "exit") {
            break;
        } else {
            cout << "Invalid command!" << endl;
        }

        cout << endl;
    }

    return 0;
}