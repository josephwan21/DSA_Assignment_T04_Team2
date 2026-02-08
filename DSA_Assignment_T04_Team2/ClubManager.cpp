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
- Advanced Feature: Allow members to record play of a game + other members who played the game and who won the game + Search game history and Sort game history
------------------------------------------------------------
*/

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


// --- Nigel Tasks: File I/O & Transactions ---
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
// Nigel ToDo: Read games.csv line by line using stringstream
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
        string borrowedDate, returnDate, reviewsStr;
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
        getline(ss, reviewsStr, ',');

        bool isBorrowed = !borrowedDate.empty();

        Game* g = new Game(name, minP, maxP, minT, maxT, year, rating, isBorrowed);
        g->setBorrowDate(borrowedDate);
        g->setReturnDate(returnDate);

        // Parse reviews if any
        if (!reviewsStr.empty()) {
            stringstream rss(reviewsStr);
            string singleReview;
            while (getline(rss, singleReview, ';')) {
                string rID, rName, rRatingStr, rComment;
                stringstream rss2(singleReview);
                getline(rss2, rID, '|');
                getline(rss2, rName, '|');
                getline(rss2, rRatingStr, '|');
                getline(rss2, rComment, '|');
                int rRating = stoi(rRatingStr);
                g->addReview(rID, rName, rRating, rComment);
            }
        }
        allGames.add(*g);
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

void ClubManager::loadGameHistory(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No game history file found at " << filename << ". Starting fresh.\n";
        return;
    }

    string line;
    bool firstLine = true;
    while (getline(file, line)) {
        if (firstLine) { firstLine = false; continue; }

        stringstream ss(line);
        string gName, playerCountStr, playersStr, winner;

        getline(ss, gName, ',');
        getline(ss, playerCountStr, ',');
        getline(ss, playersStr, ',');
        getline(ss, winner, ',');

        GamePlayRecord r;
        r.gameName = gName.substr(1, gName.size() - 2); // remove quotes
        r.playerCount = stoi(playerCountStr);
        r.winnerID = winner;

        stringstream ps(playersStr);
        string player;
        int idx = 0;
        while (getline(ps, player, ';') && idx < MAX_PLAYERS) {
            r.players[idx++] = player;
        }

        history.addRecord(r);
    }

    file.close();
}



// Nigel ToDo: Update game status and member's borrowed list
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
    m->borrowGame(g->getName());
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
    m->returnGame(g->getName());
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
    file << "name,minplayers,maxplayers,minplaytime,maxplaytime,yearpublished,rating,borroweddate,returndate,reviews\n";

    GameNode* temp = allGames.get(); // head of list
    while (temp) {
        Game& g = temp->data;

        // Serialize reviews
        string reviewsStr = "";
        for (int i = 0; i < g.getReviewCount(); i++) {
            if (i > 0) {
                reviewsStr += ";";
            }
            Review r = g.getReview(i);
            reviewsStr += r.memberID + "|" + r.memberName + "|" + to_string(r.rating) + "|" + r.comment;
        }

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
            << g.getReturnDate() << ","
            << reviewsStr << "\n";

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

void ClubManager::saveGameHistory(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open game history file for saving.\n";
        return;
    }
    // Header
    file << "gameName,playerCount,players,winnerID\n";
    HistoryNode* curr = history.getHead();
    while (curr) {
        file << '"' << curr->data.gameName << "\","
            << curr->data.playerCount << ",";

        for (int i = 0; i < curr->data.playerCount; i++) {
            if (i > 0) file << ";";
            file << curr->data.players[i];
        }

        file << "," << curr->data.winnerID << "\n";

        curr = curr->next;
    }

    file.close();
    cout << "Game history saved to " << filename << endl;
}



// --- Jayme Tasks: Sorting & Filtering ---
/*
 * Function: quickSort
 * Description: Recursively sorts an array of Game objects using a pivot.
 * Input: Game* arr - array to sort, int low - starting index, int high - ending index, bool sortByYear - toggle between year or rating sort.
 * Return: void
 */
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

/*
 * Function: displaySortedByYear
 * Description: Copies games to an array, sorts them by year using QuickSort, and displays with paging.
 * Input: None
 * Return: void
 */
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

/*
 * Function: displaySortedByRating
 * Description: Copies games to an array, sorts them by rating using QuickSort, and displays with paging.
 * Input: None
 * Return: void
 */
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

/*
 * Function: searchByPlayers
 * Description: Filters games by player count, sorts matches by rating, and displays results with paging.
 * Input: int count - number of players to search for.
 * Return: void
 */
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

/*
 * Function: rateGame
 * Description: Allows a member to rate a game (1-10) and recalculates the game's average rating.
 * Input: string gName - name of game, int score - rating score.
 * Return: void
 */
void ClubManager::rateGame(string gName, string mID) {
    // Find the game using Student A's search function
    Game* g = allGames.find(gName);
    Member* m = memberTable.getMember(mID);

    if (!g) {
        cout << "Game not found.\n";
        return;
    }
    if (!m) {
        cout << "Member not found.\n";
        return;
    }

    int score;
    cout << "Enter rating (1-10): ";
    cin >> score;
    if (score < 1 || score > 10) {
        cout << "Invalid rating. Please enter a score between 1 and 10.\n";
        return;
    }

    cin.ignore(); // clear newline
    string comment;
    cout << "Enter an optional review comment (or leave empty): ";
    getline(cin, comment);

    if (g) {
        g->addRating(score); // Call Game class rating logic
        if (!comment.empty()) {
            g->addReview(mID, m->getName(), score, comment);
        }
        cout << "Successfully rated " << gName << " as " << score << "/10!\n";
        cout << "New Average Rating: " << g->getAvgRating() << endl;
    }
    else {
        cout << "Game '" << gName << "' not found in the system.\n";
    }
}


// --- Nigel Advanced Features (recordGamePlay, searchGameHistory, sortGameHistory) ---

/*
 * Function: recordGamePlay
 * Description:
 * Allows an admin or member to record a game play session,
 * including players involved and the winner.
 * Input: None
 * Return: void
 */
void ClubManager::recordGamePlay() {
    GamePlayRecord r;
    string gameName;
    cout << "Enter game name: ";
    getline(cin, r.gameName);
    Game* g = allGames.find(r.gameName);

    if (!g) {
        cout << "Game does not exist. Record cancelled.\n";
        return;
    }

    cout << "Number of players: ";
    cin >> r.playerCount;
    cin.ignore();

    for (int i = 0; i < r.playerCount; i++) {
        string pid;
        cout << "Enter player ID " << i + 1 << ": ";
        getline(cin, pid);
        if (!getMember(pid)) {
            cout << "Player ID " << pid << " does not exist. Record cancelled.\n";
            return;
        }
        r.players[i] = pid;
    }

    cout << "Enter winner ID: ";
    getline(cin, r.winnerID);

    if (!getMember(r.winnerID)) {
        cout << "Winner ID does not exist. Record cancelled.\n";
        return;
    }

    history.addRecord(r);
    cout << "Game play recorded successfully.\n";
}

/*
 * Function: searchGameHistory
 * Description: Searches game history by game name.
 * Input: string gameName - name of the game to search.
 * Return: void
 */
void ClubManager::searchGameHistory(string gameName) {
    history.searchByGame(gameName);
}

/*
 * Function: sortGameHistory
 * Description: Sorts game history records by game name.
 * Input: None
 * Return: void
 */
void ClubManager::sortGameHistory() {
    history.bubbleSortByGame();
    cout << "Game history sorted by game name.\n";
}
/////////////////////////////////////


void ClubManager::addGame(const Game& g) {
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

Game* ClubManager::findGame(const string& gName) {
    return allGames.find(gName);
}

string ClubManager::generateMemberID() {
    return "M" + to_string(nextMemberNo++);
}

Member* ClubManager::getMember(const string& mID) {
    return memberTable.getMember(mID);
}
