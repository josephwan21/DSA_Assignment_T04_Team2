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

#include "Game.h"
#include <iostream>

/*
Function: equalsIgnoreCase - Helper Function
Description: Compares two strings ignoring case sensitivity.
Input: const string& a, const string& b - strings to compare
Return: bool - true if equal (case-insensitive), false otherwise
*/
bool equalsIgnoreCase(const string& a, const string& b) {
    if (a.length() != b.length()) return false;

    for (int i = 0; i < a.length(); i++) {
        char ca = a[i];
        char cb = b[i];

        if (ca >= 'A' && ca <= 'Z') ca += 32;
        if (cb >= 'A' && cb <= 'Z') cb += 32;

        if (ca != cb) return false;
    }
    return true;
}

/*
Function: toLower - Helper Function
Description: Converts a string to lowercase.
Input: string s - the string to convert
Return: string - lowercase version of input
*/
string toLower(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + 32;
    }
    return s;
}

//Constructors
Game::Game() {
    name = "";
    minPlayers = maxPlayers = 0;
    minPlaytime = maxPlaytime = 0;
    yearPublished = 0;
    avgRating = 0;
    ratingCount = 0;
    totalRating = 0;
    isBorrowed = false;
    reviewCount = 0;
}

// Joseph ToDo: Constructor to initialize game details
Game::Game(string n, int minP, int maxP, int minT, int maxT, int year, double r, bool borrowed) {
    name = n;
    minPlayers = minP;
    maxPlayers = maxP;
    minPlaytime = minT;
    maxPlaytime = maxT;
    yearPublished = year;
    avgRating = r;
    isBorrowed = borrowed;
    ratingCount = r > 0 ? 1 : 0;
    totalRating = r;
    borrowDate = "";
    returnDate = "";
    reviewCount = 0;
}

// Getters
/*
Functions: getName / getMinPlayers / getMaxPlayers / getMinPlaytime / getMaxPlaytime / getYearPublished / getAvgRating / getIsBorrowed / getBorrowDate / getReturnDate / getBorrowerID / getReviewCount / getReview
Description: Getter functions for game attributes.
Input: int index (only for getReview)
Return: Corresponding attribute value or Review object
*/
string Game::getName() { return name; }
int Game::getMinPlayers() { return minPlayers; }
int Game::getMaxPlayers() { return maxPlayers; }
int Game::getMinPlaytime() { return minPlaytime; }
int Game::getMaxPlaytime() { return maxPlaytime; }
int Game::getYearPublished() { return yearPublished; }
double Game::getAvgRating() { return avgRating; }
bool Game::getIsBorrowed() const { return isBorrowed; }
string Game::getBorrowDate() const { return borrowDate; }
string Game::getReturnDate() const { return returnDate; }
string Game::getBorrowerID() const { return borrowerID; }
int Game::getReviewCount() const { return reviewCount; }
Review Game::getReview(int index) const { return reviews[index]; }

// Setters
/*
Function: setName / setMinPlayers / setMaxPlayers / setMinPlaytime / setMaxPlaytime / setYearPublished / setIsBorrowed / setBorrowDate / setReturnDate / setBorrowerID
Description: Setter functions to update game attributes.
Input: Corresponding type for each attribute
Return: void
*/
void Game::setName(string n) { name = n; }
void Game::setMinPlayers(int p) { minPlayers = p; }
void Game::setMaxPlayers(int p) { maxPlayers = p; }
void Game::setMinPlaytime(int t) { minPlaytime = t; }
void Game::setMaxPlaytime(int t) { maxPlaytime = t; }
void Game::setYearPublished(int y) { yearPublished = y; }
void Game::setIsBorrowed(bool status) { isBorrowed = status; }
void Game::setBorrowDate(string date) { borrowDate = date; }
void Game::setReturnDate(string date) { returnDate = date; }
void Game::setBorrowerID(const string& id) { borrowerID = id; }

// Add Rating
/*
Function: addRating
Description: Adds a new rating and updates the game's average rating.
Input: int score - rating score (1-10)
Return: void
*/
void Game::addRating(int score) {
    totalRating += score;
    ratingCount++;
    avgRating = totalRating / ratingCount;
}


// Joseph ToDo: Display details of a single game (Requirement i)
/*
Function: display
Description: Displays detailed information about the game including rating and status.
Input: none
Return: void
*/

void Game::display() {
    cout << "Game: " << name << endl;
    cout << "Players: " << minPlayers << "-" << maxPlayers << endl;
    cout << "Playtime: " << minPlaytime << "-" << maxPlaytime << " mins" << endl;
    cout << "Year: " << yearPublished << endl;
    cout << "Average Rating: " << avgRating << "/10" << endl;
    if (ratingCount == 0) cout << " (No ratings yet)";
    cout << endl;
    cout << "Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
}

// --- GameList Implementation (Data Structure 1: Linked List) ---

//Constructor for GameList
GameList::GameList() { head = nullptr; size = 0; }

// Joseph ToDo: Insert a new GameNode at the end of the list
/*
Function: add
Description: Adds a new Game to the end of the linked list.
Input: const Game& g - game to add
Return: void
*/
void GameList::add(const Game& g) {
    GameNode* newNode = new GameNode(g);
    //newNode->data = g;
    //newNode->next = nullptr;

    if (!head) head = newNode;
    else {
        GameNode* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }
    size++;
}

// --- Remove Game ---
/*
Function: remove
Description: Removes a game from the linked list by name.
Input: string name - name of the game to remove
Return: void
*/
void GameList::remove(string name) {
    if (!head) return;

    if (head->data.getName() == name) {
        GameNode* toDelete = head;
        head = head->next;
        delete toDelete;
        size--;
        return;
    }

    GameNode* temp = head;
    while (temp->next != nullptr && temp->next->data.getName() != name) {
        temp = temp->next;
    }

    if (temp->next != nullptr) {
        GameNode* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        size--;
    }
}

// Joseph ToDo: Linear Search to find a game by name
/*
Function: find
Description: Searches for a game by name (case-insensitive).
Input: string name - name of game to search
Return: Game* - pointer to game if found, nullptr otherwise
*/
Game* GameList::find(string name) {
    // Traverse list and return pointer to Game if found
    GameNode* temp = head;
    while (temp != nullptr) {
        if (equalsIgnoreCase(temp->data.getName(), name))
            return &(temp->data);
        temp = temp->next;
    }
    return nullptr;
}

// Find first available copy for borrowing
/*
Function: findAvailableCopy
Description: Finds the first available (not borrowed) copy of a game.
Input: string name - game name to search
Return: Game* - pointer to available game, nullptr if none
*/
Game* GameList::findAvailableCopy(string name) {
    GameNode* temp = head;
    while (temp) {
        if (equalsIgnoreCase(temp->data.getName(), name) &&
            !temp->data.getIsBorrowed())
        {
            return &(temp->data);
        }
        temp = temp->next;
    }
    return nullptr;
}

// Find first borrowed copy for returning
/*
Function: findBorrowedCopy
Description: Finds the first borrowed copy of a game.
Input: string name - game name to search
Return: Game* - pointer to borrowed game, nullptr if none
*/
Game* GameList::findBorrowedCopy(string name) {
    GameNode* temp = head;
    while (temp) {
        if (equalsIgnoreCase(temp->data.getName(), name) &&
            temp->data.getIsBorrowed())
        {
            return &(temp->data);
        }
        temp = temp->next;
    }
    return nullptr;
}

// ------------------- Reviews -------------------
//--- Joseph Additional Features (addReview, displayReviews, findReviewIndexByNumber) ---
/*
Function: addReview
Description: Adds or updates a review for a game, adjusting the average rating.
Input: string mID - member ID
       string mName - member name
       int rating - rating score
       string comment - review comment
Return: void
*/
void Game::addReview(const string& mID, const string& mName, int rating, const string& comment) {
    
    int index = findReviewIndexByMember(mID);

    if (index != -1) {
        // Update existing review
        totalRating -= reviews[index].rating;  // remove old rating
        reviews[index].rating = rating;
        reviews[index].comment = comment;
        totalRating += rating;

        avgRating = totalRating / ratingCount;

        cout << "Review updated successfully.\n";
        return;
    }

    if (reviewCount < MAX_REVIEWS) {
        reviews[reviewCount].memberID = mID;
        reviews[reviewCount].memberName = mName;
        reviews[reviewCount].rating = rating;
        reviews[reviewCount].comment = comment;
        reviewCount++;
    }
    else {
        cout << "Max reviews reached for " << name << endl;
    }
}


/*
Function: displayReviews
Description: Displays all reviews for a game.
Input: none
Return: void
*/
void Game::displayReviews() const {
    if (reviewCount == 0) {
        cout << "No reviews yet for " << name << ".\n";
        return;
    }

    cout << "Reviews for " << name << ":\n";
    for (int i = 0; i < reviewCount; i++) {
        cout << reviews[i].memberName << " (" << reviews[i].memberID << ") rated "
            << reviews[i].rating << "/10: " << reviews[i].comment << endl;
    }
}

/*
Function: findReviewIndexByMember
Description: Finds the index of a review written by a specific member.
Input: string memberID - member ID to search
Return: int - index of review if found, -1 otherwise
*/
int Game::findReviewIndexByMember(const string& memberID) const {
    for (int i = 0; i < reviewCount; i++) {
        if (reviews[i].memberID == memberID)
            return i;
    }
    return -1;
}


// Joseph ToDo: Destructor to delete all nodes and prevent memory leaks
GameList::~GameList() {
    GameNode* temp = head;
    while (temp) {
        GameNode* next = temp->next;
        delete temp;
        temp = next;
    }
}

/*
Function: get
Description: Returns the head pointer of the linked list.
Input: none
Return: GameNode* - pointer to the head node
*/
GameNode* GameList::get() {
    return head;
}


//--- Nigel Advanced Features (GameHistory, addRecord, searchByGame, bubbleSortByGame, displayAll) ---

/*
 * Function: GameHistory
 * Description: Constructor that initializes an empty game history list.
 * Input: None
 * Return: None
 */

GameHistory::GameHistory() {
    head = nullptr;
}

/*
 * Function: ~GameHistory
 * Description: Destructor that frees all nodes in the linked list.
 * Input: None
 * Return: None
 */

GameHistory::~GameHistory() {
    while (head) {
        HistoryNode* temp = head;
        head = head->next;
        delete temp;
    }
}

/*
 * Function: addRecord
 * Description: Adds a new gameplay record to the end of the linked list.
 * Input: GamePlayRecord r - record containing gameplay details.
 * Return: void
 */
void GameHistory::addRecord(GamePlayRecord r) {
    HistoryNode* newNode = new HistoryNode;
    newNode->data = r;
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
        return;
    }

    HistoryNode* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = newNode;
}

/*
 * Function: searchByGame
 * Description: Searches and displays gameplay records matching a given game name.
 * Input: string name - name of the game to search for.
 * Return: void
 */
void GameHistory::searchByGame(string name) {
    HistoryNode* curr = head;
    bool found = false;
    string searchName = toLower(name);
    while (curr) {
        if (toLower(curr->data.gameName) == searchName) {
            found = true;
            cout << "\nGame: " << curr->data.gameName << endl;
            cout << "Players: ";
            for (int i = 0; i < curr->data.playerCount; i++) {
                cout << curr->data.players[i] << " ";
            }
            cout << "\nWinner: " << curr->data.winnerID << endl;
        }
        curr = curr->next;
    }

    if (!found)
        cout << "No records found for this game.\n";
}

/*
 * Function: bubbleSortByGame
 * Description: Sorts the game history records alphabetically by game name.
 * Input: None
 * Return: void
 */
void GameHistory::bubbleSortByGame() {
    if (!head || !head->next) return;

    bool swapped;
    HistoryNode* ptr;
    HistoryNode* last = nullptr;

    do {
        swapped = false;
        ptr = head;

        while (ptr->next != last) {
            if (ptr->data.gameName > ptr->next->data.gameName) {
                GamePlayRecord temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = true;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);
}

/*
 * Function: displayAll
 * Description: Displays all recorded game play history.
 * Input: None
 * Return: void
 */
void GameHistory::displayAll() {
    HistoryNode* curr = head;
    if (!curr) {
        cout << "No game history available.\n";
        return;
    }

    while (curr) {
        cout << "\nGame: " << curr->data.gameName << endl;
        cout << "Players: ";
        for (int i = 0; i < curr->data.playerCount; i++)
            cout << curr->data.players[i] << " ";
        cout << "\nWinner: " << curr->data.winnerID << endl;

        curr = curr->next;
    }
}
