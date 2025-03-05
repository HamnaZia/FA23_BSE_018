#include <iostream>
#include <string>
using namespace std;

struct Task {
    int id;
    string description;
    int priority;
    Task* next;
};

class TaskManager {
private:
    Task* head;
public:
    TaskManager() : head(nullptr) {}


    void addTask(int id, string desc, int priority) {
        Task* newTask = new Task{id, desc, priority, nullptr};

        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
            return;
        }

        Task* temp = head;
        while (temp->next && temp->next->priority >= priority) {
            temp = temp->next;
        }
        newTask->next = temp->next;
        temp->next = newTask;
    }


    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        cout << "Removed Task ID: " << temp->id << " with priority " << temp->priority << "\n";
        delete temp;
    }

    void removeTaskById(int id) {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }

        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task " << id << " removed successfully.\n";
            return;
        }

        Task* temp = head;
        while (temp->next && temp->next->id != id) {
            temp = temp->next;
        }

        if (!temp->next) {
            cout << "Task ID " << id << " not found.\n";
            return;
        }

        Task* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Task " << id << " removed successfully.\n";
    }


    void displayTasks() {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        Task* temp = head;
        while (temp) {
            cout << "Task ID: " << temp->id << " | Description: " << temp->description << " | Priority: " << temp->priority << "\n";
            temp = temp->next;
        }
    }

    ~TaskManager() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TaskManager manager;
    int choice, id, priority;
    string description;

    do {
        cout << "\nTask Management System:\n";
        cout << "1. Add Task\n2. View Tasks\n3. Remove Highest Priority Task\n4. Remove Task by ID\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Description: ";
                getline(cin, description);
                cout << "Enter Priority: ";
                cin >> priority;
                manager.addTask(id, description, priority);
                break;
            case 2:
                manager.displayTasks();
                break;
            case 3:
                manager.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter Task ID to remove: ";
                cin >> id;
                manager.removeTaskById(id);
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
