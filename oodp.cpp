#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class to represent a Student
class Student {
private:
    int id;
    string name;
    int roomNumber;

public:
    // Constructor
    Student(int i, string n, int r) {
        id = i;
        name = n;
        roomNumber = r;
    }

    // Function to display student details
    void display() {
        cout << "ID: " << id << "\nName: " << name << "\nRoom No: " << roomNumber << "\n";
    }

    // Function to check student ID (for searching)
    int getId() {
        return id;
    }
};

// Class to manage the hostel system
class Hostel {
private:
    vector<Student> students;

public:
    // Function to add a student
    void addStudent(int id, string name, int room) {
        Student newStudent(id, name, room);
        students.push_back(newStudent);
        cout << "Student added successfully!\n";
    }

    // Function to display all students
    void displayStudents() {
        if (students.empty()) {
            cout << "No students registered.\n";
            return;
        }
        for (size_t i = 0; i < students.size(); i++) {
            students[i].display();
            cout << "------------------\n";
        }
    }

    // Function to search for a student by ID
    void searchStudent(int id) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                cout << "Student Found:\n";
                students[i].display();
                return;
            }
        }
        cout << "Student not found!\n";
    }
};

int main() {
    Hostel hostel;
    int choice, id, room;
    string name;

    while (true) {
        cout << "\nHostel Management System\n";
        cout << "1. Add Student\n2. Display Students\n3. Search Student\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore(); // Clear newline from buffer
            getline(cin, name);
            cout << "Enter Room No: ";
            cin >> room;
            hostel.addStudent(id, name, room);
            break;
        case 2:
            hostel.displayStudents();
            break;
        case 3:
            cout << "Enter ID to search: ";
            cin >> id;
            hostel.searchStudent(id);
            break;
        case 4:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}

