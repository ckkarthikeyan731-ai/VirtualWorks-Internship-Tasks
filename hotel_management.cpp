#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

struct Room {
    int roomNumber;
    string customerName;
    string idProof;
    bool isBooked;
    double roomTariff;
};

void bookRoom();
void checkRoomStatus();
void generateBill();

int main() {
    int choice;
    bool active = true;

    cout << "===========================================" << endl;
    cout << "      VIRTUALWORKS HOTEL MANAGEMENT        " << endl;
    cout << "===========================================" << endl;

    while (active) {
        cout << "\n1. Book a Room" << endl;
        cout << "2. View Room Records / Status" << endl;
        cout << "3. Checkout & Generate Bill" << endl;
        cout << "4. Exit Application" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a valid menu option." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: bookRoom(); break;
            case 2: checkRoomStatus(); break;
            case 3: generateBill(); break;
            case 4:
                cout << "\nExiting Hotel Management System. Have a great day!" << endl;
                active = false;
                break;
            default: cout << "Invalid choice! Select from options 1-4." << endl;
        }
    }
    return 0;
}

void bookRoom() {
    Room r;
    ofstream outFile("hotel_records.txt", ios::app); // Open in append mode

    if (!outFile) {
        cout << "Error opening database file!" << endl;
        return;
    }

    cout << "\n--- Room Booking Console ---" << endl;
    cout << "Enter Room Number: ";
    cin >> r.roomNumber;
    cin.ignore(); // Clear newline buffer

    cout << "Enter Customer Name: ";
    getline(cin, r.customerName);

    cout << "Enter ID Proof Details: ";
    getline(cin, r.idProof);

    cout << "Enter Per-Day Room Tariff ($): ";
    cin >> r.roomTariff;

    r.isBooked = true;

    // Write structure data to sequential file format
    outFile << r.roomNumber << "," << r.customerName << "," << r.idProof << "," << r.roomTariff << "\n";
    outFile.close();

    cout << "\n✔️ Room " << r.roomNumber << " has been successfully booked for " << r.customerName << "!" << endl;
}

void checkRoomStatus() {
    ifstream inFile("hotel_records.txt");
    if (!inFile) {
        cout << "\n[Notice]: No active booking records found in the database." << endl;
        return;
    }

    string line;
    cout << "\n=====================================================================" << endl;
    cout << left << setw(10) << "Room No" << setw(20) << "Customer Name" << setw(20) << "ID Proof" << setw(15) << "Tariff/Day" << endl;
    cout << "=====================================================================" << endl;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        // Parse comma-separated text values
        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        size_t p3 = line.find(',', p2 + 1);

        string rNum = line.substr(0, p1);
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        string id = line.substr(p2 + 1, p3 - p2 - 1);
        string tariff = line.substr(p3 + 1);

        cout << left << setw(10) << rNum << setw(20) << name << setw(20) << id << "$" << setw(14) << tariff << endl;
    }
    cout << "=====================================================================" << endl;
    inFile.close();
}

void generateBill() {
    int targetRoom, days;
    cout << "\nEnter Room Number for checkout: ";
    cin >> targetRoom;
    cout << "Enter total days spent: ";
    cin >> days;

    ifstream inFile("hotel_records.txt");
    ofstream tempFile("temp.txt"); // Temporary file to filter out checked-out room

    if (!inFile) {
        cout << "No booking records found." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        size_t p1 = line.find(',');
        int rNum = stoi(line.substr(0, p1));

        if (rNum == targetRoom) {
            found = true;
            size_t p2 = line.find(',', p1 + 1);
            size_t p3 = line.find(',', p2 + 1);
            string name = line.substr(p1 + 1, p2 - p1 - 1);
            double tariff =  stod(line.substr(p3 + 1));

            cout << "\n=========================================" << endl;
            cout << "             INVOICE RECEIPT             " << endl;
            cout << "=========================================" << endl;
            cout << "Customer Name : " << name << endl;
            cout << "Room Number   : " << targetRoom << endl;
            cout << "Daily Tariff  : $" << tariff << endl;
            cout << "Total Days    : " << days << endl;
            cout << "-----------------------------------------" << endl;
            cout << "TOTAL PAYABLE : $" << (tariff * days) << endl;
            cout << "=========================================" << endl;
            cout << "Checkout processing complete." << endl;
        } else {
            tempFile << line << "\n"; // Retain other rooms in system
        }
    }

    inFile.close();
    tempFile.close();

    remove("hotel_records.txt");
    rename("temp.txt", "hotel_records.txt");

    if (!found) {
        cout << "\n❌ Error: Room " << targetRoom << " is either not active or occupied." << endl;
    }
}
