#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Structure to hold contact details cleanly
struct Contact {
    string name;
    string phone;
    string email;
};

// Function declarations
void addContact();
void viewContacts();
void searchContact();
void deleteContact();

int main() {
    int choice;
    bool systemActive = true;

    cout << "===========================================" << endl;
    cout << "     VIRTUALWORKS CONTACT MANAGER PRO      " << endl;
    cout << "===========================================" << endl;

    while (systemActive) {
        cout << "\n1. Add New Contact" << endl;
        cout << "2. View All Contacts" << endl;
        cout << "3. Search Contact Details" << endl;
        cout << "4. Delete a Contact" << endl;
        cout << "5. Exit System Framework" << endl;
        cout << "Enter your choice (1-5): ";

        if (!(cin >> choice)) {
            cout << "⚠️ Input error: Please type an integer value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5:
                cout << "\nSaving records and safely shutting down engine. Goodbye!" << endl;
                systemActive = false;
                break;
            default:
                cout << "⚠️ Value out of bounds. Please select 1 through 5." << endl;
        }
    }
    return 0;
}

void addContact() {
    Contact person;
    // Open the text file in append mode so existing records aren't overwritten
    ofstream targetFile("contacts.txt", ios::app);

    if (!targetFile) {
        cout << "❌ Engine Error: Critical file access blocked." << endl;
        return;
    }

    cin.ignore(); // Flush the stream buffer before using getline
    cout << "\n--- Create New Contact ---" << endl;

    cout << "Enter Full Name: ";
    getline(cin, person.name);

    cout << "Enter Phone Number: ";
    getline(cin, person.phone);

    cout << "Enter Email Address: ";
    getline(cin, person.email);

    // Save fields using a clear comma-separated-value format
    targetFile << person.name << "," << person.phone << "," << person.email << "\n";
    targetFile.close();

    cout << "\n✔️ Contact saved permanently to local storage!" << endl;
}

void viewContacts() {
    ifstream sourceFile("contacts.txt");
    if (!sourceFile) {
        cout << "\n[System Notice]: No stored contacts found yet." << endl;
        return;
    }

    string entryLine;
    cout << "\n=====================================================================" << endl;
    cout << left << setw(20) << "Full Name" << setw(18) << "Phone Number" << setw(25) << "Email Address" << endl;
    cout << "=====================================================================" << endl;

    int totalCount = 0;
    while (getline(sourceFile, entryLine)) {
        if (entryLine.empty()) continue;

        // Parse fields via comma positions
        size_t comma1 = entryLine.find(',');
        size_t comma2 = entryLine.find(',', comma1 + 1);

        string name = entryLine.substr(0, comma1);
        string phone = entryLine.substr(comma1 + 1, comma2 - comma1 - 1);
        string email = entryLine.substr(comma2 + 1);

        cout << left << setw(20) << name << setw(18) << phone << setw(25) << email << endl;
        totalCount++;
    }
    cout << "=====================================================================" << endl;
    cout << "Total Active Records: " << totalCount << endl;
    sourceFile.close();
}

void searchContact() {
    ifstream sourceFile("contacts.txt");
    if (!sourceFile) {
        cout << "\n[System Notice]: Database empty. Nothing to search." << endl;
        return;
    }

    cin.ignore();
    string searchKey;
    cout << "\nEnter Name or Phone Number to search: ";
    getline(cin, searchKey);

    string entryLine;
    bool found = false;

    while (getline(sourceFile, entryLine)) {
        if (entryLine.empty()) continue;

        size_t comma1 = entryLine.find(',');
        size_t comma2 = entryLine.find(',', comma1 + 1);

        string name = entryLine.substr(0, comma1);
        string phone = entryLine.substr(comma1 + 1, comma2 - comma1 - 1);
        string email = entryLine.substr(comma2 + 1);

        // Smart flexible check matching name OR phone string fields
        if (name == searchKey || phone == searchKey) {
            if (!found) {
                cout << "\n🎯 Record Found Successfully:" << endl;
                cout << "---------------------------------------" << endl;
            }
            cout << "👤 Name   : " << name << endl;
            cout << "📞 Phone  : " << phone << endl;
            cout << "📧 Email  : " << email << endl;
            cout << "---------------------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "\n❌ Search complete: No records match '" << searchKey << "'." << endl;
    }
    sourceFile.close();
}

void deleteContact() {
    ifstream sourceFile("contacts.txt");
    if (!sourceFile) {
        cout << "\n[System Notice]: Database empty. Nothing to delete." << endl;
        return;
    }

    cin.ignore();
    string targetName;
    cout << "\nEnter the EXACT Full Name of the contact to delete: ";
    getline(cin, targetName);

    ofstream tempFile("temp_contacts.txt"); // Workspace file to write records we want to keep
    string entryLine;
    bool matchesFound = false;

    while (getline(sourceFile, entryLine)) {
        if (entryLine.empty()) continue;

        size_t comma1 = entryLine.find(',');
        string currentName = entryLine.substr(0, comma1);

        // If it matches our target name, skip writing it to the temporary file
        if (currentName == targetName) {
            matchesFound = true;
        } else {
            tempFile << entryLine << "\n";
        }
    }

    sourceFile.close();
    tempFile.close();

    // Standard high-level pipeline swap operation
    remove("contacts.txt");
    rename("temp_contacts.txt", "contacts.txt");

    if (matchesFound) {
        cout << "\n✔️ Target record has been successfully scrubbed from disk storage." << endl;
    } else {
        cout << "\n❌ Error: Could not locate a contact with that name." << endl;
    }
}
