#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Task {
public:
    Task(const std::string& desc) : description(desc), completed(false) {}
    
    std::string getDescription() const {
        return description;
    }
    
    bool isCompleted() const {
        return completed;
    }
    
    void markAsCompleted() {
        completed = true;
    }

private:
    std::string description;
    bool completed;
};

void displayTasks(const std::vector<Task>& tasks) {
    std::cout << "\nTasks:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i].getDescription();
        if (tasks[i].isCompleted()) {
            std::cout << " [Completed]";
        }
        std::cout << "\n";
    }
}

void saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file("tasks.txt");
    for (const auto& task : tasks) {
        file << task.getDescription() << "|" << (task.isCompleted() ? "1" : "0") << "\n";
    }
    file.close();
}

std::vector<Task> loadTasks() {
    std::vector<Task> tasks;
    std::ifstream file("tasks.txt");
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('|');
        if (pos != std::string::npos) {
            std::string description = line.substr(0, pos);
            bool completed = line.substr(pos + 1) == "1";
            Task task(description);
            if (completed) {
                task.markAsCompleted();
            }
            tasks.push_back(task);
        }
    }
    file.close();
    return tasks;
}

int main() {
    std::vector<Task> tasks = loadTasks();

    while (true) {
        std::cout << "\nTask Manager\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. List Tasks\n";
        std::cout << "3. Mark Task as Completed\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
            case 1: {
                std::cout << "Enter task description: ";
                std::string description;
                std::getline(std::cin, description);
                tasks.push_back(Task(description));
                break;
            }
            case 2:
                displayTasks(tasks);
                break;
            case 3: {
                std::cout << "Enter task number to mark as completed: ";
                int taskNumber;
                std::cin >> taskNumber;
                std::cin.ignore(); 
                if (taskNumber > 0 && taskNumber <= tasks.size()) {
                    tasks[taskNumber - 1].markAsCompleted();
                } else {
                    std::cout << "Invalid task number.\n";
                }
                break;
            }
            case 4:
                saveTasks(tasks);
                return 0;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}
