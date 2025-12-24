# 📝 C++ Todo Manager

A console-based task manager written in C++ to practice data structures and STL containers, with clean output, file saving, and simple task handling.

## 📸 Preview

<img width="623" height="703" alt="image" src="https://github.com/user-attachments/assets/3bc36c10-ad85-4f55-b684-b5379f0cf1ae" />

## ✨ Features

- ➕ Create tasks with description and status
- 📋 Display all tasks in formatted list
- ✅ Mark tasks as completed/incompleted
- ✏️ Edit existing task descriptions
- 🔍 Search tasks by keyword
- 🗑️ Delete tasks from list
- 💾 File persistence - tasks saved between sessions
- 📊 View task statistics (completed/pending)
- 🎨 Colorful terminal interface with emojis
- ⚡ Real-time command processing
- 🛡️ Comprehensive error handling and input validation
- 🆘 Built-in help system
- 🧹 Console clearing for better UX

## 🛠️ Technology Stack

- C++17
- Standard Template Library (STL)
- File I/O operations
- Command-line interface

## 🚀 Getting Started

```bash
# Clone the repository
git clone https://github.com/Pupler/CPP-Todo-Manager.git

# Compile and run
cd CPP-Todo-Manager
g++ main.cpp -o todo
./todo
```

## 🎮 Usage Commands

```bash
list                           # Show all tasks with statistics
add                            # Add a new task
complete [number]              # Mark task as completed
uncomplete [number]            # Mark task as incomplete
edit [number]                  # Edit task description
search [text]                  # Search in task descriptions
delete [number]                # Delete a task
help                           # Show available commands
clear                          # Clear console screen
exit                           # Quit program
```

## 📁 Data Persistence

- Tasks are automatically saved to ```tasks.txt``` after every modification
- Data loads automatically on program startup
- Format: ```description|status|category|timestamp``` (e.g., Buy milk|0|Shopping|1765367015)

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.
