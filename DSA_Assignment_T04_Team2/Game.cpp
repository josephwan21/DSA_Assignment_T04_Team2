#include "Game.h"
#include <iostream>
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

// Student A ToDo: Constructor to initialize game details
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
string Game::getName() { return name; }
int Game::getMinPlayers() { return minPlayers; }
int Game::getMaxPlayers() { return maxPlayers; }
int Game::getMinPlaytime() { return minPlaytime; }
int Game::getMaxPlaytime() { return maxPlaytime; }
int Game::getYearPublished() { return yearPublished; }
double Game::getAvgRating() { return avgRating; }
bool Game::getIsBorrowed() const { return isBorrowed; }

// Setters
void Game::setName(string n) { name = n; }
void Game::setMinPlayers(int p) { minPlayers = p; }
void Game::setMaxPlayers(int p) { maxPlayers = p; }
void Game::setMinPlaytime(int t) { minPlaytime = t; }
void Game::setMaxPlaytime(int t) { maxPlaytime = t; }
void Game::setYearPublished(int y) { yearPublished = y; }
void Game::setIsBorrowed(bool status) { isBorrowed = status; }

// Add Rating
void Game::addRating(int score) {
    totalRating += score;
    ratingCount++;
    avgRating = totalRating / ratingCount;
}


// Student A ToDo: Display details of a single game (Requirement i)
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

GameList::GameList() { head = nullptr; size = 0; }

// Student A ToDo: Insert a new GameNode at the end of the list
void GameList::add(Game g) {
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

// Student A ToDo: Linear Search to find a game by name
Game* GameList::find(string name) {
    // Traverse list and return pointer to Game if found
    GameNode* temp = head;
    while (temp != nullptr) {
        if (temp->data.getName() == name) return &(temp->data);
        temp = temp->next;
    }
    return nullptr;
}

// Find first available copy for borrowing
Game* GameList::findAvailableCopy(string name) {
    GameNode* temp = head;
    while (temp) {
        if (temp->data.getName() == name && !temp->data.getIsBorrowed())
            return &(temp->data);
        temp = temp->next;
    }
    return nullptr;
}

// Find first borrowed copy for returning
Game* GameList::findBorrowedCopy(string name) {
    GameNode* temp = head;
    while (temp) {
        if (temp->data.getName() == name && temp->data.getIsBorrowed())
            return &(temp->data);
        temp = temp->next;
    }
    return nullptr;
}

// ------------------- Reviews -------------------

void Game::addReview(const string& mID, const string& mName, int rating, const string& comment) {
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

// Student A ToDo: Destructor to delete all nodes and prevent memory leaks
GameList::~GameList() {
    GameNode* temp = head;
    while (temp) {
        GameNode* next = temp->next;
        delete temp;
        temp = next;
    }
}

GameNode* GameList::get() {
    return head;
}


//Newly Added GameHistory Implementation (Record Play of Game)//
GameHistory::GameHistory() {
    head = nullptr;
}

GameHistory::~GameHistory() {
    while (head) {
        HistoryNode* temp = head;
        head = head->next;
        delete temp;
    }
}


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
void GameHistory::searchByGame(string name) {
    HistoryNode* curr = head;
    bool found = false;

    while (curr) {
        if (curr->data.gameName == name) {
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
