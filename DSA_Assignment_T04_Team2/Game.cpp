#include "Game.h"
#include <iostream>

// Student A ToDo: Constructor to initialize game details
Game::Game(string n, int minP, int maxP, int minT, int maxT, int year) {
    name = "";
    minPlayers = maxPlayers = 0;
    minPlaytime = maxPlaytime = 0;
    yearPublished = 0;
    avgRating = 0;
    isBorrowed = false;
    ratingCount = 0;
    totalRating = 0;
}

// Getters
string Game::getName() { return name; }
int Game::getMinPlayers() { return minPlayers; }
int Game::getMaxPlayers() { return maxPlayers; }
int Game::getMinPlaytime() { return minPlaytime; }
int Game::getMaxPlaytime() { return maxPlaytime; }
int Game::getYearPublished() { return yearPublished; }
double Game::getAvgRating() { return avgRating; }
bool Game::getIsBorrowed() { return isBorrowed; }

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
    cout << "Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
}

// --- GameList Implementation (Data Structure 1: Linked List) ---

GameList::GameList() { head = nullptr; size = 0; }

// Student A ToDo: Insert a new GameNode at the end of the list
void GameList::add(Game g) {
    GameNode* newNode = new GameNode;
    newNode->data = g;
    newNode->next = nullptr;

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

// Student A ToDo: Destructor to delete all nodes and prevent memory leaks
GameList::~GameList() { /* delete nodes */ }