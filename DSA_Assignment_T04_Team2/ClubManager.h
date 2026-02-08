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
*/

#ifndef CLUBMANAGER_H
#define CLUBMANAGER_H
#include "Game.h"
#include "Member.h"
using namespace std;

class ClubManager {
private:
    GameList allGames;       // Managed by Student A's Linked List
    MemberHash memberTable;  // Managed by Student A's Hash Table
    int nextMemberNo;
    int displayLimit = 10;
	GameHistory history; // Newly Added

public:
    ClubManager();

    // --- Student B Tasks (Operations & File IO) ---
    // Student B ToDo: Open games.csv, parse lines using stringstream, and populate allGames
    void loadData(string filename);
    void loadMembers(string filename);
    void loadGameHistory(const string& filename);
    // Student B ToDo: Implementation for Borrow/Return logic
    void borrowGame(string mID, string gName);
    void addGame(const Game& g);
    void addMember(Member m);
    void removeGame(string gName);
    void returnGame(string mID, string gName);
    void displayAdminSummary();
    void displayMemberSummary(string mID);
	void saveGames(string filename);
    void saveMembers(string filename);
    void saveGameHistory(const string& filename);
    Game* findGame(const string& gName);
    Member* getMember(const string& mID);
	void recordGamePlay();   // Newly Added
	void searchGameHistory(string gameName); // Newly Added
	void sortGameHistory();  // Newly Added


    // --- Jayme Tasks (Search, Sort, Ratings) ---
    // Jayme ToDo: Copy GameList to a temporary Array and implement MergeSort or QuickSort
    void displaySortedByYear();
    void displaySortedByRating();
    // Jayme ToDo: Implementation of player count filtering
    void searchByPlayers(int count);
    void rateGame(string gName, string mID);
    string generateMemberID();

    void setDisplayLimit(int limit) { displayLimit = limit; }
    int getDisplayLimit() const { return displayLimit; }
};
#endif