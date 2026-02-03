#include "ClubManager.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;


string getCurrentDate() {
    time_t t = time(nullptr);
    tm now{}; // note: initialize to zero
    localtime_s(&now, &t); // safe version

    stringstream ss;
    ss << (now.tm_year + 1900) << "-"        // year
        << setw(2) << setfill('0') << (now.tm_mon + 1) << "-" // month
        << setw(2) << setfill('0') << now.tm_mday;           // day
    return ss.str(); // YYYY-MM-DD
}


// --- Student B Tasks: File I/O & Transactions ---
ClubManager::ClubManager()
{
    nextMemberNo = 1000;
}

string trimQuotes(const string& s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        return s.substr(1, s.size() - 2);
    return s;
}

string getNextField(stringstream& ss) {
    string field;
    if (ss.peek() == '"') { // field starts with a quote
        getline(ss, field, '"'); // skip opening quote
        getline(ss, field, '"'); // read until closing quote
        if (ss.peek() == ',') ss.ignore(); // skip the comma after closing quote
    }
    else {
        getline(ss, field, ','); // normal field
    }
    return field;
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
    bool firstLine = true; //skip header
    while (getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }
        stringstream ss(line);
        string nameStr = getNextField(ss);
        string borrowedDate, returnDate;
        int minP, maxP, minT, maxT, year;
        double rating;
        //getline(ss, nameStr, ',');
        string name = trimQuotes(nameStr);
        ss >> minP; ss.ignore();
        ss >> maxP; ss.ignore();
        ss >> minT; ss.ignore();
        ss >> maxT; ss.ignore();
        ss >> year; ss.ignore();
        ss >> rating; ss.ignore();
        getline(ss, borrowedDate, ',');
        getline(ss, returnDate, ',');

        bool isBorrowed = !borrowedDate.empty();

        Game g(name, minP, maxP, minT, maxT, year, rating, isBorrowed);
        g.setBorrowDate(borrowedDate);
        g.setReturnDate(returnDate);
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

    Game* g = allGames.findAvailableCopy(gName);
    
    if (!g) {
        cout << "Game is not available for borrowing. Select another game to borrow.\n";
        return;
    }

    g->setIsBorrowed(true);
    g->setBorrowDate(getCurrentDate());
    g->setReturnDate("");
    m->borrowGame(gName);
    cout << "Success! " << m->getName() << " (Member ID: " <<  mID << ") borrowed " << gName << endl;
}


void ClubManager::returnGame(string mID, string gName) {
    Member* m = memberTable.getMember(mID);
    if (!m) {
        cout << "Member not found!\n";
        return;
    }

    Game* g = allGames.findBorrowedCopy(gName);
    if (!g) {
        cout << "No borrowed copy found!\n";
        return;
    }

    g->setIsBorrowed(false);
    g->setBorrowDate("");
    g->setReturnDate(getCurrentDate());
    m->returnGame(gName);
    cout << "Game returned successfully.\n";
}

//Add new function
void ClubManager::displayAdminSummary() {
    int borrowed = 0, available = 0;

    GameNode* temp = allGames.get();  // or make head accessible via getter
    while (temp) {
        if (temp->data.getIsBorrowed())
            borrowed++;
        else
            available++;
        temp = temp->next;
    }

    cout << "\n--- Admin Summary ---\n";
    cout << "Borrowed games: " << borrowed << endl;
    cout << "Available games: " << available << endl;
}

//Add new function
void ClubManager::displayMemberSummary(string mID) {
    Member* m = memberTable.getMember(mID);

    if (m == nullptr) {
        cout << "Member not found.\n";
        return;
    }

    cout << "\n--- Member Summary ---\n";
    cout << "Member ID: " << m->getID() << endl;
    cout << "Name: " << m->getName() << endl;

    m->displayBorrowedGames();  // delegated to Member class
}

// Save all game data back to CSV
void ClubManager::saveGames(const string filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Failed to open file for saving.\n";
        return;
    }

    // Write header
    file << "name,minplayers,maxplayers,minplaytime,maxplaytime,yearpublished,rating,borroweddate,returndate\n";

    GameNode* temp = allGames.get(); // head of list
    while (temp) {
        Game& g = temp->data;

        string outName = g.getName();
        if (outName.find(',') != string::npos) outName = "\"" + outName + "\"";

        file << outName << ","
            << g.getMinPlayers() << ","
            << g.getMaxPlayers() << ","
            << g.getMinPlaytime() << ","
            << g.getMaxPlaytime() << ","
            << g.getYearPublished() << ","
            << g.getAvgRating() << ","
            << g.getBorrowDate() << ","
            << g.getReturnDate() << "\n";

        temp = temp->next;
    }

    file.close();
    cout << "Games saved successfully to " << filename << "\n";
}




// --- Student C Tasks: Sorting & Filtering ---

// Student C ToDo: Implement a Sorting Algorithm (Data Structure 3: Array for Sorting)
void quickSort(Game* arr, int low, int high, bool byYear) {
    if (low < high) {
        // Simple partition logic
        double pivot = byYear ? arr[high].getYearPublished() : arr[high].getAvgRating();
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            double currentVal = byYear ? arr[j].getYearPublished() : arr[j].getAvgRating();

            // Sort Descending for Rating, Ascending for Year
            bool condition = byYear ? (currentVal < pivot) : (currentVal > pivot);

            if (condition) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSort(arr, low, pi - 1, byYear);
        quickSort(arr, pi + 1, high, byYear);
    }
}

void ClubManager::displaySortedByYear() {
    // 1. Count total games to create array
    int count = 0;
    GameNode* temp = allGames.get();
    while (temp) { count++; temp = temp->next; }

    if (count == 0) return;

    // 2. Copy GameList into a temporary Game array
    Game* tempArray = new Game[count];
    temp = allGames.get();
    for (int i = 0; i < count; i++) {
        tempArray[i] = temp->data;
        temp = temp->next;
    }

    // 3. Perform Sort
    quickSort(tempArray, 0, count - 1, true);

    // 4. Print results
    cout << "\n--- Games Sorted by Year Published ---\n";
    for (int i = 0; i < count; i++) {
        tempArray[i].display();
        cout << "--------------------------" << endl;
    }
    delete[] tempArray;
}

void ClubManager::displaySortedByRating() {
    int count = 0;
    GameNode* temp = allGames.get();
    while (temp) { count++; temp = temp->next; }

    if (count == 0) {
        cout << "No games loaded in the system. Check if games.csv is in the correct folder.\n";
        return;
    }

    Game* tempArray = new Game[count];
    temp = allGames.get();
    for (int i = 0; i < count; i++) {
        tempArray[i] = temp->data;
        temp = temp->next;
    }

    quickSort(tempArray, 0, count - 1, false);

    cout << "\n--- Top Rated Games (Showing top " << displayLimit << ") ---\n";
    // Student C: Added displayLimit check here
    int limit = (count < displayLimit) ? count : displayLimit;
    for (int i = 0; i < limit; i++) {
        tempArray[i].display();
        cout << "--------------------------" << endl;
    }
    delete[] tempArray;
}

void ClubManager::searchByPlayers(int count) {
    cout << "\n--- Results for " << count << " players ---" << endl;
    GameNode* curr = allGames.get();
    int foundCount = 0;
    while (curr && foundCount < displayLimit) {
        if (count >= curr->data.getMinPlayers() && count <= curr->data.getMaxPlayers()) {
            curr->data.display();
            cout << "--------------------------" << endl;
            foundCount++;
        }
        curr = curr->next;
    }
    if (foundCount == 0) cout << "No games match that player count." << endl;
}

void ClubManager::rateGame(string gName, int score) {
    Game* g = allGames.find(gName); // Uses Student A's search
    if (g) {
        g->addRating(score);
        cout << "Rating updated! New average: " << g->getAvgRating() << "/10" << endl;
    }
    else {
        cout << "Game not found." << endl;
    }
}

void ClubManager::addGame(Game g) {
    allGames.add(g);
    cout << "Game added successfully.\n";
}

void ClubManager::addMember(Member m) {
    memberTable.addMember(m);
    cout << "Member added successfully.\n";
}

void ClubManager::removeGame(string gName) {
    if (allGames.find(gName) == nullptr) {
        cout << "Game does not exist.\n";
    }
    else {
        allGames.remove(gName);
        cout << "Game removed successfully.\n";
    }    
}

string ClubManager::generateMemberID() {
    return "M" + to_string(nextMemberNo++);
}

Member* ClubManager::getMember(const string& mID) {
    return memberTable.getMember(mID);
}
