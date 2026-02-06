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
    void saveMembers(string filename);
    // Student B ToDo: Implementation for Borrow/Return logic
    void borrowGame(string mID, string gName);
    void addGame(Game g);
    void addMember(Member m);
    void removeGame(string gName);
    void returnGame(string mID, string gName);
    void displayAdminSummary();
    void displayMemberSummary(string mID);
	void saveGames(string filename);
    Game* findGame(const string& gName);
    Member* getMember(const string& mID);
	void recordGamePlay();   // Newly Added
	void searchGameHistory(string gameName); // Newly Added
	void sortGameHistory();  // Newly Added


    // --- Student C Tasks (Search, Sort, Ratings) ---
    // Student C ToDo: Copy GameList to a temporary Array and implement MergeSort or QuickSort
    void displaySortedByYear();
    void displaySortedByRating();
    // Student C ToDo: Implementation of player count filtering
    void searchByPlayers(int count);
    void rateGame(string gName, string mID);
    string generateMemberID();

    void setDisplayLimit(int limit) { displayLimit = limit; }
    int getDisplayLimit() const { return displayLimit; }
};
#endif