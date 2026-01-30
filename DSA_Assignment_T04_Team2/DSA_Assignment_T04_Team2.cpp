#include <iostream>
#include <string>
#include <limits>
#include "ClubManager.h"

using namespace std;

// --- Function Prototypes for Student C ---
void displayMainMenu();
void displayAdminMenu();
void displayMemberMenu();
void clearInput();

int main() {
    ClubManager manager;

    // // Student B ToDo: manager.loadData("games.csv");

    int mainChoice = 0;
    bool running = true;

    while (running) {
        displayMainMenu();
        cout << "Select Role: ";
        if (!(cin >> mainChoice)) { clearInput(); continue; }

        if (mainChoice == 1) { // Administrator
            displayAdminMenu();
            int adminChoice;
            cin >> adminChoice;

            switch (adminChoice) {
            case 1:
                // // Student A ToDo: manager.addGame(newGame);
                break;
            case 2:
                // // Student A ToDo: manager.removeGame(gameName);
                break;
            case 3:
                // // Student A ToDo: manager.addMember(newMember);
                break;
            case 4:
                // // Student B ToDo: manager.displayAdminSummary();
                break;
            }

        }
        else if (mainChoice == 2) { // Member
            string mID;
            cout << "Enter Member ID: ";
            cin >> mID;

            // In a real scenario, you'd verify mID here via manager.getMember(mID)

            displayMemberMenu();
            int memChoice;
            cin >> memChoice;

            switch (memChoice) {
            case 1:
                // // Student B ToDo: manager.performBorrow(mID, gameName);
                break;
            case 2:
                // // Student B ToDo: manager.performReturn(mID, gameName);
                break;
            case 3:
                // // Student B ToDo: manager.displayMemberSummary(mID);
                break;
            case 4:
                // // Student C ToDo: manager.rateGame(gameName, score);
                break;
            }

        }
        else if (mainChoice == 3) { // Universal search/sort
            // // Student C ToDo: manager.searchByPlayers(count);
            // // Student C ToDo: manager.displaySortedByRating();
        }
        else if (mainChoice == 4) {
            // // Student B ToDo: manager.saveGames("games.csv");
            running = false;
        }
    }
    return 0;
}

// --- Menu Implementations ---

void displayMainMenu() {
    cout << "\n================================" << endl;
    cout << "   NPTTGC MANAGEMENT SYSTEM" << endl;
    cout << "================================" << endl;
    cout << "1. Administrator" << endl;
    cout << "2. Member" << endl;
    cout << "3. Search & Sort Games" << endl;
    cout << "4. Exit" << endl;
}

void displayAdminMenu() {
    cout << "\n--- Administrator Menu ---" << endl;
    cout << "1. Add a new board game" << endl;
    cout << "2. Remove a board game" << endl;
    cout << "3. Add a new member" << endl;
    cout << "4. Display summary of games borrowed/returned" << endl;
}

void displayMemberMenu() {
    cout << "\n--- Member Menu ---" << endl;
    cout << "1. Borrow a board game" << endl;
    cout << "2. Return a board game" << endl;
    cout << "3. Display my borrowed/returned summary" << endl;
    cout << "4. Rate a game (1-10)" << endl;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please try again." << endl;
}
