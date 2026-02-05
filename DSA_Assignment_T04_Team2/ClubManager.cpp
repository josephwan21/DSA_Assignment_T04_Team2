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
    ifstream file(filename);
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

void ClubManager::loadMembers(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No members file found. Starting fresh.\n";
        return;
    }

    string line;
    bool firstLine = true;

    while (getline(file, line)) {
        if (firstLine) { firstLine = false; continue; }

        stringstream ss(line);
        string id, name;

        getline(ss, id, ',');
        getline(ss, name, ',');

        if (!id.empty() && !name.empty()) {
            Member m(id, name);
            memberTable.addMember(m);

            // Keep member IDs consistent
            int num = stoi(id.substr(1));
            if (num >= nextMemberNo)
                nextMemberNo = num + 1;
        }
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

void ClubManager::saveMembers(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to save members.\n";
        return;
    }

    file << "memberID,name\n";

    HashNode** table = memberTable.getTable();
    for (int i = 0; i < 101; i++) {
        HashNode* temp = table[i];
        while (temp) {
            file << temp->member.getID() << ","
                << temp->member.getName() << "\n";
            temp = temp->next;
        }
    }

    file.close();
    cout << "Members saved successfully to " << filename << "\n";
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
    int count = 0;
    GameNode* temp = allGames.get();
    while (temp) { count++; temp = temp->next; }

    if (count == 0) return;

    Game* tempArray = new Game[count];
    temp = allGames.get();
    for (int i = 0; i < count; i++) {
        tempArray[i] = temp->data;
        temp = temp->next;
    }

    quickSort(tempArray, 0, count - 1, true); // Sort by Year

    int currentIndex = 0;
    char choice = 'n';

    do {
        cout << "\n--- Games by Year (Page " << (currentIndex / displayLimit) + 1 << ") ---\n";
        int endOfPage = (currentIndex + displayLimit > count) ? count : currentIndex + displayLimit;

        for (int i = currentIndex; i < endOfPage; i++) {
            cout << "[" << i + 1 << "] ";
            tempArray[i].display();
            cout << "--------------------------" << endl;
        }

        if (endOfPage < count) {
            cout << "Show next page? (y/n): ";
            cin >> choice;
            currentIndex += displayLimit;
        }
        else {
            cout << "No more games to show.\n";
            choice = 'n';
        }
    } while (choice == 'y' || choice == 'Y');

    delete[] tempArray;
}

void ClubManager::displaySortedByRating() {
    int count = 0;
    GameNode* temp = allGames.get();
    while (temp) { count++; temp = temp->next; }

    if (count == 0) return;

    // Copy to temporary array for sorting
    Game* tempArray = new Game[count];
    temp = allGames.get();
    for (int i = 0; i < count; i++) {
        tempArray[i] = temp->data;
        temp = temp->next;
    }

    quickSort(tempArray, 0, count - 1, false); // Sort by Rating Descending

    int currentIndex = 0;
    char choice = 'n';

    do {
        cout << "\n--- Top Rated Games (Page " << (currentIndex / displayLimit) + 1 << ") ---\n";

        int endOfPage = currentIndex + displayLimit;
        if (endOfPage > count) endOfPage = count;

        for (int i = currentIndex; i < endOfPage; i++) {
            cout << "[" << i + 1 << "] ";
            tempArray[i].display();
            cout << "--------------------------" << endl;
        }

        if (endOfPage < count) {
            cout << "Show next " << displayLimit << " games? (y/n): ";
            cin >> choice;
            currentIndex += displayLimit;
        }
        else {
            cout << "End of list reached.\n";
            choice = 'n';
        }
    } while (choice == 'y' || choice == 'Y');

    delete[] tempArray;
}

void ClubManager::searchByPlayers(int count) {
    // 1. First, count how many games match the criteria to allocate array size
    int matchCount = 0;
    GameNode* temp = allGames.get();
    while (temp) {
        if (count >= temp->data.getMinPlayers() && count <= temp->data.getMaxPlayers()) {
            matchCount++;
        }
        temp = temp->next;
    }

    if (matchCount == 0) {
        cout << "No games found suitable for " << count << " players." << endl;
        return;
    }

    // 2. Copy only the matching games into a temporary array
    Game* matchArray = new Game[matchCount];
    temp = allGames.get();
    int index = 0;
    while (temp) {
        if (count >= temp->data.getMinPlayers() && count <= temp->data.getMaxPlayers()) {
            matchArray[index++] = temp->data;
        }
        temp = temp->next;
    }

    // 3. Sort the matches by Average Rating (Descending)
    quickSort(matchArray, 0, matchCount - 1, false); // false = sort by rating

    // 4. Implement Paging Display
    int currentIndex = 0;
    char choice = 'n';

    do {
        cout << "\n--- Games for " << count << " Players (Sorted by Rating - Page " << (currentIndex / displayLimit) + 1 << ") ---\n";

        int endOfPage = (currentIndex + displayLimit > matchCount) ? matchCount : currentIndex + displayLimit;

        for (int i = currentIndex; i < endOfPage; i++) {
            cout << "[" << i + 1 << "] ";
            matchArray[i].display();
            cout << "--------------------------" << endl;
        }

        if (endOfPage < matchCount) {
            cout << "Show next " << displayLimit << " matching games? (y/n): ";
            cin >> choice;
            currentIndex += displayLimit;
        }
        else {
            cout << "End of matching results.\n";
            choice = 'n';
        }
    } while (choice == 'y' || choice == 'Y');

    delete[] matchArray;
}

void ClubManager::rateGame(string gName, int score) {
    if (score < 1 || score > 10) {
        cout << "Invalid rating. Please enter a score between 1 and 10.\n";
        return;
    }

    // Find the game using Student A's search function
    Game* g = allGames.find(gName);
    if (g) {
        g->addRating(score); // Call Game class rating logic
        cout << "Successfully rated " << gName << " as " << score << "/10!\n";
        cout << "New Average Rating: " << g->getAvgRating() << endl;
    }
    else {
        cout << "Game '" << gName << "' not found in the system.\n";
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
