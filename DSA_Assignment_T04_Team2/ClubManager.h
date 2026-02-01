#ifndef CLUBMANAGER_H
#define CLUBMANAGER_H
#include "Game.h"
#include "Member.h"

class ClubManager {
private:
    GameList allGames;       // Managed by Student A's Linked List
    MemberHash memberTable;  // Managed by Student A's Hash Table

public:
    ClubManager();

    // --- Student B Tasks (Operations & File IO) ---
    // Student B ToDo: Open games.csv, parse lines using stringstream, and populate allGames
    void loadData(string filename);
    // Student B ToDo: Implementation for Borrow/Return logic
    void borrowGame(string mID, string gName);
    void addGame(Game g);
    void addMember(Member m);
    void removeGame(string gName);
    void returnGame(string mID, string gName);

    // --- Student C Tasks (Search, Sort, Ratings) ---
    // Student C ToDo: Copy GameList to a temporary Array and implement MergeSort or QuickSort
    void displaySortedByYear();
    // Student C ToDo: Implementation of player count filtering
    void searchByPlayers(int count);
};
#endif