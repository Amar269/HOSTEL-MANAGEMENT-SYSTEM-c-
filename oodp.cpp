#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
    int id;
    char name[50];
    int roomNo;
    char department[50];

public:
    void input() {
        cout << "\nEnter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Room Number: ";
        cin >> roomNo;
        cin.ignore();
        cout << "Enter Department: ";
        cin.getline(department, 50);
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nRoom No: " << roomNo;
        cout << "\nDepartment: " << department << "\n";
    }

    int getID() {
        return id;
    }
};

void addStudent() {
    Student s;
    ofstream outFile("hostel.dat", ios::binary | ios::app);
    s.input();
    outFile.write((char*)&s, sizeof(s));
    outFile.close();
    cout << "\nStudent record added successfully!\n";
}

void displayAll() {
    Student s;
    ifstream inFile("hostel.dat", ios::binary);
    if (!inFile) {
        cout << "\nNo data found!\n";
        return;
    }
    while (inFile.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "-----------------------------\n";
    }
    inFile.close();
}

void searchStudent() {
    int id;
    Student s;
    cout << "\nEnter Student ID to search: ";
    cin >> id;

    ifstream inFile("hostel.dat", ios::binary);
    bool found = false;
    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.getID() == id) {
            cout << "\nStudent found:\n";
            s.display();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) cout << "\nStudent not found!\n";
}

void updateStudent() {
    int id;
    cout << "\nEnter Student ID to update: ";
    cin >> id;

    fstream file("hostel.dat", ios::binary | ios::in | ios::out);
    Student s;
    bool found = false;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getID() == id) {
            cout << "\nEnter new details:\n";
            s.input();
            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));
            cout << "\nRecord updated successfully!\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "\nStudent not found!\n";
}

void deleteStudent() {
    int id;
    cout << "\nEnter Student ID to delete: ";
    cin >> id;

    ifstream inFile("hostel.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    Student s;
    bool found = false;

    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.getID() != id) {
            outFile.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }
    inFile.close();
    outFile.close();

    remove("hostel.dat");
    rename("temp.dat", "hostel.dat");

    if (found)
        cout << "\nRecord deleted successfully!\n";
    else
        cout << "\nStudent not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\n===== Hostel Management System =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "\nExiting program...\n"; break;
            default: cout << "\nInvalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
