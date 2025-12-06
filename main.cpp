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

void showStats(vector<Task>& tasks) {
    int count_completed = 0;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].is_completed == true) {
            count_completed++;
        }
    }

    cout << "📊 " << "Total: " << tasks.size() << " tasks (✅ "
    << count_completed << " done, " << "⏳ "
    << tasks.size() - count_completed << " pending)\n" << endl;
}

void showHeader() {
    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║         📝 C++ TODO MANAGER          ║\n";
    cout << "╚══════════════════════════════════════╝\n";
    cout << "Commands: list, add, complete, help, clear, exit" << endl;
}

void showTasksList(vector<Task>& tasks) {
    cout << "╔══════════════════════════════════════╗\n";
    cout << "║            📋 TASKS LIST             ║\n";
    cout << "╚══════════════════════════════════════╝\n";
    showStats(tasks);
    if (!tasks.empty()) {
        for (int i = 0; i < tasks.size(); i++) {
            cout << "┌─[" << i+1 << "]─ " << tasks[i].description << "\n";
            cout << "│   Status: " << (tasks[i].is_completed ? "[\033[32m✅ DONE\033[0m]" : "[\033[31m⏳ PENDING\033[0m]") << "\n";
            cout << "└─────────────────────────────────────\n";
        }
        return;
    }

    cout << "Tasks list is empty. Use command 'add' to add a new task." << endl;
}

void showHelp() {
    cout << "Available commands:" << endl;
    cout << "  list - Show all tasks" << endl;
    cout << "  add - Add a new task" << endl;
    cout << "  complete [task number] - Complete task" << endl;
    cout << "  delete [task number] - Delete task" << endl;
    cout << "  help - Show this help" << endl;
    cout << "  clear - Clear console" << endl;
    cout << "  exit - Quit program" << endl;
}

void addTask(vector<Task>& tasks) {
    string taskDesc;

    cout << "Enter task description: ";
    getline(cin, taskDesc);

    if (!taskDesc.empty()) {
        tasks.push_back(Task(taskDesc, false));
        cout << "Task added!" << endl;
        return;
    }

    cout << "Error: Task description is empty!" << endl;
}

void completeTask(string& input, vector<Task>& tasks) {
    try {
        string str_num = input.substr(9);
        int task_num = stoi(str_num);

        if (task_num < 1 || task_num > tasks.size()) {
            cout << "Error: Task " << task_num << " doesn't exist!" << endl;
            return;
        }

        if (tasks[task_num - 1].is_completed == false) {
            tasks[task_num - 1].is_completed = true;
            cout << "Task " << task_num << " completed!" << endl;
            return;
        } else {
            cout << "Task is already completed!" << endl;
            return;
        }
    }
    catch(...) {
        cout << "Invalid task number!" << endl;
    }
}

void deleteTask(string& input, vector<Task>& tasks) {
    try {
        string str_num = input.substr(7);
        int task_num = stoi(str_num);

        if (task_num < 1 || task_num > tasks.size()) {
            cout << "Error: Task " << task_num << " doesn't exist!" << endl;
            return;
        }

        tasks.erase(tasks.begin() + (task_num - 1));
        cout << "Task " << task_num << " was successfully deleted!" << endl;
    }
    catch(...) {
        cout << "Invalid task number!" << endl;
    }
}

int main() {
    vector<Task> tasks;
    string input;
    // tasks.push_back(Task("Buy a bread", false));
    // tasks.push_back(Task("Do homework", true));
    // tasks.push_back(Task("Learn C#", false));

    showHeader();

    while (true) {
        cout << endl;
        cout << "\033[1;36m";
        cout << "> ";
        getline(cin, input);
        cout << "\033[0m";

        if (input.empty()) {
            continue;
        } else if (input == "list") {
            showTasksList(tasks);
        } else if (input == "add") {
            addTask(tasks);
        } else if (input == "clear") {
            system("clear");
            showHeader();
        } else if (input.rfind("complete ", 0) == 0) {
            completeTask(input, tasks);
        } else if (input.rfind("delete ", 0) == 0) {
            deleteTask(input, tasks);
        } else if (input == "help") {
            showHelp();
        } else if (input == "exit") {
            break;
        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}