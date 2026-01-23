#include "ClubManager.h"
#include <fstream>
#include <sstream>

// --- Student B Tasks: File I/O & Transactions ---

// Student B ToDo: Read games.csv line by line using stringstream
void ClubManager::loadData(string filename) {
    // 1. Open file using ifstream
    // 2. Loop through lines, split by comma
    // 3. allGames.add(new Game(...))
}

// Student B ToDo: Update game status and member's borrowed list
void ClubManager::borrowGame(string mID, string gName) {
    // 1. memberTable.getMember(mID)
    // 2. allGames.find(gName)
    // 3. Update 'isBorrowed' status and dates
}

// --- Student C Tasks: Sorting & Filtering ---

// Student C ToDo: Implement a Sorting Algorithm (Data Structure 3: Array for Sorting)
void ClubManager::displaySortedByYear() {
    // 1. Copy GameList into a temporary Game array[size]
    // 2. Perform QuickSort or BubbleSort on the array by yearPublished
    // 3. Print the sorted results
}

// Student C ToDo: Filter and display games for a specific player count
void ClubManager::searchByPlayers(int count) {
    // Traverse GameList and print games where min <= count <= max
}