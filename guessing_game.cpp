#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

void playGame();

int main() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

    int choice;
    bool keepPlaying = true;

    cout << "===========================================" << endl;
    cout << "   WELCOME TO THE NUMBER GUESSING GAME     " << endl;
    cout << "===========================================" << endl;

    while (keepPlaying) {
        cout << "\n1. Play Game\n2. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter 1 or 2.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            playGame();
        } else if (choice == 2) {
            cout << "\nThank you for playing! See you next time.\n" << endl;
            keepPlaying = false;
        } else {
            cout << "Invalid selection. Please choose 1 or 2.\n";
        }
    }

    return 0;
}

void playGame() {
    // Generate a random number between 1 and 100
    int targetNumber = (rand() % 100) + 1;
    int userGuess = 0;
    int attempts = 0;

    cout << "\n[System]: I have selected a random number between 1 and 100." << endl;
    cout << "Can you guess what it is?" << endl;

    // Loop until the user guesses the correct number
    while (userGuess != targetNumber) {
        cout << "\nEnter your guess: ";

        // Validate input to ensure it's an integer
        if (!(cin >> userGuess)) {
            cout << "Error: That's not a valid number. Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        attempts++;

        // Provide smart hints
        if (userGuess > targetNumber) {
            if (userGuess - targetNumber > 20) {
                cout << "-> Too High! (Way off)" << endl;
            } else {
                cout << "-> High, but you are getting close!" << endl;
            }
        } else if (userGuess < targetNumber) {
            if (targetNumber - userGuess > 20) {
                cout << "-> Too Low! (Way off)" << endl;
            } else {
                cout << "-> Low, but you are getting close!" << endl;
            }
        } else {
            cout << "\n🎉 Congratulations! You guessed the correct number: " << targetNumber << endl;
            cout << "🏆 Total attempts taken: " << attempts << endl;
        }
    }
}
