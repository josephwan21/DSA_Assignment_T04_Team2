/*
------------------------------------------------------------
T04 Team 2
Joseph Bacomo Wan Zi Jun S10262528
Jayme Chua Jie-Ming S10257137
Nigel Ng Hong Jie S10262591

Jayme (S10257137):
- Task 1: Designed the Hierarchical Menu System (Admin vs. Member views).
- Task 2: Utilized an array for temporary game storage to facilitate efficient sorting.
- Task 3: Implemented QuickSort to sort games by Rating, Year, or Player Count.
- Task 4: Implemented "Rate a Game" logic with dynamic average rating recalculation.
- Additional Feature: Added custom settings for display limits and paging logic.
------------------------------------------------------------
Nigel (S10262591):
- Task 1: Create the CSV Parser to read/write games.csv.
- Task 2: Implement the Borrow/Return logic to check if a game is available and updating the borroweddate and returndate.
- Task 3: Implement a Linked List to manage the "Transaction History" (Summary of games borrowed/returned).
- Task 4: Create the "Admin Summary" view.
- Additional Feature: Allow members to record play of a game + other members who played the game and who won the game + Search game history and Sort game history
------------------------------------------------------------
Joseph (S10262528)
- Task 1: Implement the Game and Member classes.
Game Class: Stores name, player counts, playtimes, year, average rating, and status (Available/Borrowed).
Member Class: Stores Member ID, name, and an array of currently borrowed games.
- Task 2: Implement a Hash Table to store Members. This allows O(1) or O(log n) lookup when a member logs in or an admin adds a new member.
- Task 3: Implement Linear Search or Binary Search (if sorted) to find specific games by name or filter by the number of players.
- Task 4: Handle the "Display details of a particular game" feature.
- Additional Feature: Allow members to write a review of the game. Users can read the reviews for a game, and each review shows the member who wrote it and their rating for the game.
------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <limits>
#include "ClubManager.h"
#include <vector>
using namespace std;

/*
 * Function: displayMainMenu
 * Description: Renders the primary entry point for Administrators and Members.
 * Input: None
 * Return: void
 */
void displayMainMenu();

/*
 * Function: displayAdminMenu
 * Description: Renders management options for game and member administration.
 * Input: None
 * Return: void
 */
void displayAdminMenu();

/*
 * Function: displayMemberMenu
 * Description: Renders the interface for members to borrow, return, and rate games.
 * Input: None
 * Return: void
 */
void displayMemberMenu();
/*
 * Function: clearInput
 * Description: Clears invalid input from cin to prevent input errors.
 * Input: None
 * Return: void
 */
void clearInput();

// Admin actions
/*
 * Function: handleAddGame
 * Description: Prompts the admin to input details for a new game and adds it to the ClubManager.
 * Input: ClubManager& manager - reference to the club manager instance
 * Return: void
 */
void handleAddGame(ClubManager& manager);

/*
 * Function: handleRemoveGame
 * Description: Prompts the admin to specify a game to remove from ClubManager.
 * Input: ClubManager& manager - reference to the club manager instance
 * Return: void
 */
void handleRemoveGame(ClubManager& manager);

/*
 * Function: handleAddMember
 * Description: Prompts the admin for a member name, generates a member ID, and adds the member to ClubManager.
 * Input: ClubManager& manager - reference to the club manager instance
 * Return: void
 */
void handleAddMember(ClubManager& manager);

int main() {
    ClubManager manager;

    // // Nigel ToDo: manager.loadData("games.csv");
    manager.loadData("games.csv");
    manager.loadMembers("members.csv");
    manager.loadGameHistory("game_history.csv");

    int mainChoice = 0;
    bool running = true;

    while (running) {
        displayMainMenu();
        cout << "Select Role/Option: ";
        if (!(cin >> mainChoice)) { clearInput(); continue; }

        if (mainChoice == 1) { // Administrator
            bool adminRunning = true;
            while (adminRunning) {
                displayAdminMenu();
                int adminChoice;
                cin >> adminChoice;

                switch (adminChoice) {
                case 1:
                    // // Joseph ToDo: manager.addGame(newGame);
                    handleAddGame(manager);
                    break;
                case 2:
                    // // Joseph ToDo: manager.removeGame(gameName);
                    handleRemoveGame(manager);
                    break;
                case 3:
                    // // Joseph ToDo: manager.addMember(newMember);
                    handleAddMember(manager);
                    break;
                case 4:
                    // // Nigel ToDo: manager.displayAdminSummary();
                    manager.displayAdminSummary();
                    break;
                case 0:
                    adminRunning = false;
                    break;
                default:
                    cout << "Invalid option. Please try again.\n";
                    break;
                }
            }
        }
        else if (mainChoice == 2) { // Member
            string mID;
            Member* memberPtr = nullptr;
            do {
                cout << "Enter Member ID (0 to cancel): ";
                cin >> mID;

                if (mID == "0") {
                    cout << "Returning to main menu.\n";
                    break;
                }

                memberPtr = manager.getMember(mID);
                if (!memberPtr) {
                    cout << "Member not found. Please enter a valid Member ID.\n";
                }
            } while (!memberPtr);

            if (!memberPtr) {
                continue;
            }

            cout << "\nWelcome, " << memberPtr->getName() << " (Member ID: " << memberPtr->getID() << ")!\n";

            bool memberRunning = true;
            while (memberRunning) {
                displayMemberMenu();
                int memChoice;
                cin >> memChoice;

                string gameName;
                switch (memChoice) {
                case 1: {
                    // // Nigel ToDo: manager.performBorrow(mID, gameName);
                    cin.ignore();
                    cout << "Enter game name to borrow: ";
                    getline(cin, gameName);
                    manager.borrowGame(mID, gameName);
                    break;
                }
                case 2: {
                    // // Nigel ToDo: manager.performReturn(mID, gameName);
                    cin.ignore();
                    cout << "Enter game name to return: ";
                    getline(cin, gameName);
                    manager.returnGame(mID, gameName);
                    break;
                }
                case 3:
                    // // Nigel ToDo: manager.displayMemberSummary(mID);
                    manager.displayMemberSummary(mID);
                    break;
                case 4:
                    // Jayme ToDo: manager.rateGame(gameName, score);
                    cin.ignore();
                    cout << "Enter game name to rate: ";
                    getline(cin, gameName);
                    manager.rateGame(gameName, mID);
                    break;
                case 5: {
                    cin.ignore();
                    cout << "Enter game name to view reviews: ";
                    getline(cin, gameName);

                    Game* g = manager.findGame(gameName);
                    if (!g) {
                        cout << "Game not found.\n";
                    }
                    else {
                        g->displayReviews();
                    }
                    break;
                }
                case 6: {
                    cin.ignore();
                    manager.recordGamePlay();
                    break;
                }

                case 0:
                    memberRunning = false;
                    break;
                default:
                    cout << "Invalid option. Please try again.\n";
                    break;
                }
            }
        }
        else if (mainChoice == 3) {
            cout << "1. Sort by Rating\n2. Sort by Year\n3. Search by Player Count\n4. Search game history\n5. Sort game history\nChoice: ";
            int subChoice; cin >> subChoice;
            if (subChoice == 1) manager.displaySortedByRating();
            else if (subChoice == 2) manager.displaySortedByYear();
            else if (subChoice == 3) {
                int pCount; cout << "Enter players: "; cin >> pCount;
                manager.searchByPlayers(pCount);
            }
			else if (subChoice == 4) {
                cin.ignore();
				string gName;
				cout << "Enter game name to search history: ";
				getline(cin, gName);
				manager.searchGameHistory(gName);
			}
			else if (subChoice == 5) {
				manager.sortGameHistory();
			}
        }
        else if (mainChoice == 4) { // NEW: Settings Menu
            cout << "\n--- Settings ---\n";
            cout << "Current display limit: " << manager.getDisplayLimit() << endl;
            cout << "Set new limit (e.g., 5, 10, 50): ";
            int newLimit;
            if (cin >> newLimit) {
                manager.setDisplayLimit(newLimit);
                cout << "Limit updated successfully.\n";
            }
            else {
                clearInput();
            }
        }
        else if (mainChoice == 0) {
            // // Student B ToDo: manager.saveGames("games.csv");
			manager.saveGames("games.csv");
            manager.saveMembers("members.csv");
            manager.saveGameHistory("game_history.csv");
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
    cout << "4. Settings" << endl;
    cout << "0. Exit" << endl;
}

void displayAdminMenu() {
    cout << "\n--- Administrator Menu ---" << endl;
    cout << "1. Add a new board game" << endl;
    cout << "2. Remove a board game" << endl;
    cout << "3. Add a new member" << endl;
    cout << "4. Display summary of games borrowed/returned" << endl;
    cout << "0. Exit Admin Menu" << endl;
    cout << "Select option: ";
}

void displayMemberMenu() {
    cout << "\n--- Member Menu ---" << endl;
    cout << "1. Borrow a board game" << endl;
    cout << "2. Return a board game" << endl;
    cout << "3. Display my borrowed/returned summary" << endl;
    cout << "4. Rate a game (1-10)" << endl;
    cout << "5. View reviews for a game" << endl;
	cout << "6. Record a game play session" << endl;
    cout << "0. Exit Member Menu" << endl;
    cout << "Select option: ";
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please try again." << endl;
}

// ---------- Admin Functions ----------
void handleAddGame(ClubManager& manager) {
    string name;
    int minP, maxP, minT, maxT, year;

    cin.ignore();
    cout << "Enter game name: "; getline(cin, name);
    cout << "Min players: "; cin >> minP;
    cout << "Max players: "; cin >> maxP;
    cout << "Min playtime: "; cin >> minT;
    cout << "Max playtime: "; cin >> maxT;
    cout << "Year published: "; cin >> year;

    Game g(name, minP, maxP, minT, maxT, year, 0, false);
    manager.addGame(g);
}

void handleRemoveGame(ClubManager& manager) {
    cin.ignore();
    string gameName;
    cout << "Enter game name to remove: ";
    getline(cin, gameName);
    manager.removeGame(gameName);
}

void handleAddMember(ClubManager& manager) {
    string mName;
    cin.ignore();
    cout << "Enter member name: "; 
    getline(cin, mName);
    string mID = manager.generateMemberID();
    Member m(mID, mName);
    manager.addMember(m);
    cout << "Generated Member ID: " << mID << endl;
}