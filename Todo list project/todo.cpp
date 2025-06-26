#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Task {
public:
    string description;
    bool isDone;

    Task(string desc, bool done = false) {
        description = desc;
        isDone = done;
    }
};

class ToDoList {
private:
    vector<Task> tasks;
    const string filename = "tasks.txt";

    void saveToFile() {
        ofstream file(filename);
        for (const auto &task : tasks) {
            file << task.isDone << "|" << task.description << "\n";
        }
        file.close();
    }

    void loadFromFile() {
        tasks.clear();
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            size_t sep = line.find('|');
            if (sep != string::npos) {
                bool done = (line.substr(0, sep) == "1");
                string desc = line.substr(sep + 1);
                tasks.emplace_back(desc, done);
            }
        }
        file.close();
    }

public:
    ToDoList() {
        loadFromFile();
    }

    void addTask(const string &desc) {
        tasks.emplace_back(desc);
        saveToFile();
        cout << "✅ Task added.\n";
    }

    void showTasks() {
        if (tasks.empty()) {
            cout << "📭 No tasks found.\n";
            return;
        }
        cout << "\n📋 To-Do List:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". [" << (tasks[i].isDone ? "✔" : " ") << "] "
                 << tasks[i].description << "\n";
        }
    }

    void markDone(int index) {
        if (index < 1 || index > tasks.size()) {
            cout << "❌ Invalid task number.\n";
            return;
        }
        tasks[index - 1].isDone = true;
        saveToFile();
        cout << "✅ Task marked as done.\n";
    }

    void deleteTask(int index) {
        if (index < 1 || index > tasks.size()) {
            cout << "❌ Invalid task number.\n";
            return;
        }
        tasks.erase(tasks.begin() + index - 1);
        saveToFile();
        cout << "🗑 Task deleted.\n";
    }
};

int main() {
    ToDoList todo;
    int choice;

    while (true) {
        cout << "\n===== TO-DO LIST MANAGER =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Done\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(); // clear newline from input buffer

        if (choice == 1) {
            string task;
            cout << "Enter task description: ";
            getline(cin, task);
            todo.addTask(task);
        } else if (choice == 2) {
            todo.showTasks();
        } else if (choice == 3) {
            int num;
            cout << "Enter task number to mark as done: ";
            cin >> num;
            todo.markDone(num);
        } else if (choice == 4) {
            int num;
            cout << "Enter task number to delete: ";
            cin >> num;
            todo.deleteTask(num);
        } else if (choice == 5) {
            cout << "👋 Exiting. Goodbye!\n";
            break;
        } else {
            cout << "⚠ Invalid option.\n";
        }
    }

    return 0;
}
