#include <iostream>
#include <limits>

using namespace std;

// Global array matrix representing the 3x3 game board
char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char currentMarker;
int currentPlayer;

// Function prototypes
void displayBoard();
bool placeMarker(int slot);
int checkWinner();
void swapPlayerAndMarker();
void runGame();

int main() {
    cout << "===========================================" << endl;
    cout << "     WELCOME TO VIRTUALWORKS TIC-TAC-TOE   " << endl;
    cout << "===========================================" << endl;

    int choice;
    bool running = true;

    while (running) {
        cout << "\n1. Start New Game\n2. Exit Application\n";
        cout << "Enter selection: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter 1 or 2.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            runGame();
        } else if (choice == 2) {
            cout << "\nThank you for playing! Exiting code framework..." << endl;
            running = false;
        } else {
            cout << "Selection out of range. Try again.\n" << endl;
        }
    }
    return 0;
}

// Renders the updated state of the 3x3 game grid
void displayBoard() {
    cout << "\n     |     |     " << endl;
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  " << endl;
    cout << "     |     |     \n" << endl;
}

// Translates a 1-9 user input into matrix row/column and updates the array
bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    // Verify cell hasn't already been taken by an 'X' or 'O'
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentMarker;
        return true;
    }
    return false;
}

// Scans rows, columns, and diagonals to see if any winning combinations align
int checkWinner() {
    // Check all rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return currentPlayer;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return currentPlayer;
    }
    // Check principal and secondary diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return currentPlayer;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return currentPlayer;

    return 0; // Return 0 if no winner is detected yet
}

// Alternate back and forth between player 1 (X) and player 2 (O)
void swapPlayerAndMarker() {
    if (currentMarker == 'X') {
        currentMarker = 'O';
        currentPlayer = 2;
    } else {
        currentMarker = 'X';
        currentPlayer = 1;
    }
}

// Handles core setup, moves, and reset operations for a fresh match
void runGame() {
    // Reset the board array values for a fresh run
    char initialValues[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
            board[i][j] = initialValues[i][j];

    currentPlayer = 1;
    currentMarker = 'X';

    int winner = 0;
    int totalMoves = 0;

    displayBoard();

    while (winner == 0 && totalMoves < 9) {
        int slot;
        cout << "Player " << currentPlayer << " (" << currentMarker << "), enter a slot (1-9): ";

        if (!(cin >> slot) || slot < 1 || slot > 9) {
            cout << "⚠️ Invalid spot. Choose a regular number from 1 to 9." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Validate choice and record move if the slot is clear
        if (!placeMarker(slot)) {
            cout << "⚠️ That slot is already occupied! Try a different one." << endl;
            continue;
        }

        displayBoard();
        totalMoves++;
        winner = checkWinner();

        if (winner == 0 && totalMoves < 9) {
            swapPlayerAndMarker();
        }
    }

    if (winner != 0) {
        cout << "🎉 Brilliant! Player " << winner << " has won the match!" << endl;
    } else {
        cout << "🤝 Excellent defense from both sides! The match ends in a Draw." << endl;
    }
}
