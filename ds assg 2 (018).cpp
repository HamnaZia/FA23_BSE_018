#include <iostream>
#include <string>
using namespace std;


class Patient {
public:
    string name;
    int arrivalOrder;
    string condition;
    int priority;

    Patient(string n = "", int arrival = 0, string cond = "", int pri = 0) {
        name = n;
        arrivalOrder = arrival;
        condition = cond;
        priority = pri;
    }
};

class PriorityQueue {
private:
    Patient patients[100];
    int size;
    int nextArrival;


    int assignPriority(string condition) {
        if (condition == "Heart Attack" || condition == "Stroke") {
            return 1;
        } else if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm") {
            return 2;
        } else if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine") {
            return 3;
        } else if (condition == "Mild Cold" || condition == "Small Cut") {
            return 4;
        } else {
            return 4;
        }
    }

    void sortPatients() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (patients[j].priority > patients[j + 1].priority) {
                    Patient temp = patients[j];
                    patients[j] = patients[j + 1];
                    patients[j + 1] = temp;
                }
            }
        }
    }

public:
    PriorityQueue() {
        size = 0;
        nextArrival = 1;
    }

    void addPatient(string name, string condition) {
        int priority = assignPriority(condition);
        patients[size] = Patient(name, nextArrival++, condition, priority);
        size++;
        sortPatients();
        cout << "Patient " << name << " added with priority " << priority << endl;
        displayQueue();
    }

    void treatPatient() {
        if (size == 0) {
            cout << "No patients in the queue!" << endl;
            return;
        }
        cout << "Treating patient: " << patients[0].name << " (" << patients[0].condition
             << ", Priority: " << patients[0].priority << ")" << endl;

        for (int i = 0; i < size - 1; i++) {
            patients[i] = patients[i + 1];
        }
        size--;
        displayQueue();
    }

    void displayQueue() {
        cout << "Current Treatment Order:" << endl;
        cout << "-----------------------------" << endl;
        cout << "| Name\t| Arrival | Condition\t| Priority |" << endl;
        cout << "-----------------------------" << endl;
        if (size == 0) {
            cout << "| (Empty)\t\t\t\t\t|" << endl;
        } else {
            for (int i = 0; i < size; i++) {
                cout << "| " << patients[i].name << "\t| " << patients[i].arrivalOrder
                     << "\t  | " << patients[i].condition << "\t| " << patients[i].priority
                     << "\t   |" << endl;
            }
        }
        cout << "-----------------------------" << endl;
    }
};

int main() {
    PriorityQueue hospital;

    string givenNames[] = {"Patient A", "Patient B", "Patient C", "Patient D", "Patient E",
                          "Patient F", "Patient G", "Patient H", "Patient I", "Patient J"};
    string givenConditions[] = {"Fever", "Heart Attack", "Broken Leg", "Mild Cold", "Severe Burn",
                               "Small Cut", "Stroke", "Food Poisoning", "Fractured Arm", "Migraine"};


    for (int i = 0; i < 10; i++) {
        hospital.addPatient(givenNames[i], givenConditions[i]);
    }

    while (true) {
        cout << "\nHospital Menu:" << endl;
        cout << "1. Add a new patient" << endl;
        cout << "2. Treat the next patient" << endl;
        cout << "3. Show treatment order" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name, condition;
            cout << "Enter patient name: ";
            getline(cin, name);
            cout << "Enter emergency condition (e.g., Fever, Heart Attack): ";
            getline(cin, condition);
            hospital.addPatient(name, condition);
        } else if (choice == 2) {
            hospital.treatPatient();
        } else if (choice == 3) {
            hospital.displayQueue();
        } else if (choice == 4) {
            cout << "Exiting program." << endl;
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
