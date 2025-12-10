#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

struct Task {
    string description;
    bool is_completed;
    time_t created_at;

    Task(const string& desc, bool is_compltd = false, time_t created = time(nullptr)) {
        description = desc;
        is_completed = is_compltd;
        created_at = created;
    }
};

void writeIntoFile(vector<Task>& tasks) {
    ofstream writeFile("tasks.txt"); // write file (.txt)

    for (int i = 0; i < tasks.size(); i++) {
        writeFile << tasks[i].description << "|" << tasks[i].is_completed << "|" << tasks[i].created_at << endl;
    }
}

void loadFromFile(vector<Task>& tasks) {
    string task_description;
    bool task_is_completed;
    time_t task_created_at;
    string line;
    ifstream readFile("tasks.txt");

    while (getline(readFile, line)) {
        size_t pos1 = line.find("|"); // position number
        size_t pos2 = line.find("|", pos1 + 1); // position number
        
        task_description = line.substr(0, pos1);
        
        string str_num_task_status = line.substr(pos1 + 1, 1);
        int task_status = stoi(str_num_task_status);
        task_is_completed = task_status;

        string str_num_task_created_at = line.substr(pos2 + 1);
        task_created_at = stoll(str_num_task_created_at);

        tasks.push_back(Task(task_description, task_is_completed, task_created_at));
    }
}

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
    cout << "Commands: list, add, edit, complete, help, clear, exit" << endl;
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
            cout << "│   Created at: " << ctime(&tasks[i].created_at);
            cout << "└───────────────────────────────────────\n";
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
    cout << "  uncomplete [task number] - Uncomplete task" << endl;
    cout << "  delete [task number] - Delete task" << endl;
    cout << "  edit [task number] - Edit task" << endl;
    cout << "  search [text] - Search tasks" << endl;
    cout << "  help - Show this help" << endl;
    cout << "  clear - Clear console" << endl;
    cout << "  exit - Quit program" << endl;
}

void addTask(vector<Task>& tasks) {
    string taskDesc;

    cout << "Enter task description: ";
    getline(cin, taskDesc);

    if (!taskDesc.empty()) {
        tasks.push_back(Task(taskDesc));
        writeIntoFile(tasks);
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
            writeIntoFile(tasks);
            cout << "Task " << task_num << " was marked completed!" << endl;
            return;
        } else {
            cout << "Task is already completed!" << endl;
            return;
        }
    } catch(...) {
        cout << "Invalid task number!" << endl;
    }
}

void unCompleteTask(string& input, vector<Task>& tasks) {
    try {
        string str_num = input.substr(11);
        int task_num = stoi(str_num);

        if (task_num < 1 || task_num > tasks.size()) {
            cout << "Error: Task " << task_num << " doesn't exist!" << endl;
            return;
        }

        if (tasks[task_num - 1].is_completed == true) {
            tasks[task_num - 1].is_completed = false;
            writeIntoFile(tasks);
            cout << "Task " << task_num << " was marked uncompleted!" << endl;
            return;
        } else {
            cout << "Task is not completed yet!" << endl;
            return;
        }
    } catch(...) {
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
        writeIntoFile(tasks);
        cout << "Task " << task_num << " was successfully deleted!" << endl;
    } catch(...) {
        cout << "Invalid task number!" << endl;
    }
}

void editTask(string& input, vector<Task>& tasks) {
    try {
        string str_num = input.substr(5);
        int task_num = stoi(str_num);
        string newTaskDesc;

        if (task_num < 1 || task_num > tasks.size()) {
            cout << "Error: Task " << task_num << " doesn't exist!" << endl;
            return;
        }

        cout << "Enter new task description: ";
        getline(cin, newTaskDesc);

        if (!newTaskDesc.empty()) {
            tasks[task_num - 1].description = newTaskDesc;
            writeIntoFile(tasks);
            cout << "Task " << task_num << " was successfully edited!" << endl;
            return;
        }

        cout << "Task description is empty!" << endl;
    } catch(...) {
        cout << "Invalid task number!" << endl;
    }
}

void searchTask(string& input, vector<Task>& tasks) {
    bool found = false;
    string taskSearchDesc = input.substr(7);

    if (taskSearchDesc.empty()) {
        cout << "Error: Search query is empty!" << endl;
        return;
    }

    cout << "🔎 Result of searching '" << taskSearchDesc << "':" << endl;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].description.find(taskSearchDesc) != string::npos) {
            cout << "[" << i + 1 << "] " << tasks[i].description << " - " << (tasks[i].is_completed ? "✅" : "⏳") << endl;
            found = true;
        }
    }

    if (found == false) {
        cout << "No tasks found!" << endl;
    }
}

int main() {
    vector<Task> tasks;
    string input;

    showHeader();
    loadFromFile(tasks);

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
        } else if (input.rfind("uncomplete ", 0) == 0) {
            unCompleteTask(input, tasks);
        } else if (input.rfind("delete ", 0) == 0) {
            deleteTask(input, tasks);
        } else if (input.rfind("edit ", 0) == 0) {
            editTask(input, tasks);
        } else if (input.rfind("search ", 0) == 0) {
            searchTask(input, tasks);
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