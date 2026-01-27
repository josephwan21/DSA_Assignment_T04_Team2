#include "ClubManager.h"
#include <fstream>
#include <sstream>

// --- Student B Tasks: File I/O & Transactions ---
ClubManager::ClubManager()
{
	// Constructor implementation (if needed)
}
// Student B ToDo: Read games.csv line by line using stringstream
void ClubManager::loadData(string filename) 
{
    // 1. Open file using ifstream
    // 2. Loop through lines, split by comma
    // 3. allGames.add(new Game(...))
    ifstream file("games.csv");
    if (!file.is_open()) {
        cout << "Failed to open file.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int minP, maxP, minT, maxT, year;

        getline(ss, name, ',');
        ss >> minP; ss.ignore();
        ss >> maxP; ss.ignore();
        ss >> minT; ss.ignore();
        ss >> maxT; ss.ignore();
        ss >> year;

        Game g(name, minP, maxP, minT, maxT, year);
        allGames.add(g);
    }

    file.close();

}

// Student B ToDo: Update game status and member's borrowed list
void ClubManager::borrowGame(string mID, string gName) 
{
    // 1. memberTable.getMember(mID)
    // 2. allGames.find(gName)
    // 3. Update 'isBorrowed' status and dates
    Member* m = memberTable.getMember(mID);
    if (!m) {
        cout << "Member not found!\n";
        return;
    }

    Game* g = allGames.find(gName);
    if (!g) {
        cout << "Game not found!\n";
        return;
    }

    if (g->getIsBorrowed()) {
        cout << "Game already borrowed!\n";
        return;
    }

    g->setIsBorrowed(true);
    m->borrowGame(gName);
    cout << "Success! " << mID << " borrowed " << gName << endl;

}

// --- Student C Tasks: Sorting & Filtering ---

// Student C ToDo: Implement a Sorting Algorithm (Data Structure 3: Array for Sorting)
void ClubManager::displaySortedByYear() 
{
    // 1. Copy GameList into a temporary Game array[size]
    // 2. Perform QuickSort or BubbleSort on the array by yearPublished
    // 3. Print the sorted results
}

// Student C ToDo: Filter and display games for a specific player count
void ClubManager::searchByPlayers(int count) 
{
    // Traverse GameList and print games where min <= count <= max
}