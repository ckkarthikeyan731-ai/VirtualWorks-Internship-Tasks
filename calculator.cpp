#include <iostream>
#include <limits>

using namespace std;

// Function prototypes for clarity and structure
void displayMenu();
void performCalculation(int choice);

int main() {
    int choice;
    bool keepRunning = true;

    cout << "=== Welcome to the VirtualWorks Calculator Application ===" << endl;

    while (keepRunning) {
        displayMenu();
        cout << "Enter your choice (1-5): ";

        // Handle non-integer inputs gracefully
        if (!(cin >> choice)) {
            cout << "\nInvalid input! Please enter a number between 1 and 5.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 5) {
            cout << "\nThank you for using the Calculator App. Exiting program..." << endl;
            keepRunning = false;
        } else if (choice >= 1 && choice <= 4) {
            performCalculation(choice);
        } else {
            cout << "\nError: Invalid selection. Please choose an option from the menu.\n" << endl;
        }
    }

    return 0;
}

// Function to print a clean menu interface
void displayMenu() {
    cout << "-----------------------------------" << endl;
    cout << "        MATHEMATICAL MENU          " << endl;
    cout << "-----------------------------------" << endl;
    cout << "1. Addition (+)" << endl;
    cout << "2. Subtraction (-)" << endl;
    cout << "3. Multiplication (*)" << endl;
    cout << "4. Division (/)" << endl;
    cout << "5. Exit Application" << endl;
    cout << "-----------------------------------" << endl;
}

// Function to handle the operations
void performCalculation(int choice) {
    double num1, num2, result;

    cout << "\nEnter first number: ";
    while (!(cin >> num1)) {
        cout << "Invalid input. Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter second number: ";
    while (!(cin >> num2)) {
        cout << "Invalid input. Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (choice) {
        case 1:
            result = num1 + num2;
            cout << "\n>>> Result: " << num1 << " + " << num2 << " = " << result << "\n" << endl;
            break;
        case 2:
            result = num1 - num2;
            cout << "\n>>> Result: " << num1 << " - " << num2 << " = " << result << "\n" << endl;
            break;
        case 3:
            result = num1 * num2;
            cout << "\n>>> Result: " << num1 << " * " << num2 << " = " << result << "\n" << endl;
            break;
        case 4:
            // Critical edge-case handling for division by zero
            if (num2 == 0) {
                cout << "\n[Math Error]: Division by zero is undefined!\n" << endl;
            } else {
                result = num1 / num2;
                cout << "\n>>> Result: " << num1 << " / " << num2 << " = " << result << "\n" << endl;
            }
            break;
        default:
            cout << "\nAn unexpected error occurred.\n" << endl;
    }
}
