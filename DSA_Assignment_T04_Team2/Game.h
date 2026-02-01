#ifndef GAME_H
#define GAME_H
#include <string>
#include <iostream>
using namespace std;

class Game {
private:
    string name;
    int minPlayers, maxPlayers, minPlaytime, maxPlaytime, yearPublished;
    double avgRating;
    bool isBorrowed;
    int ratingCount;      // Number of ratings
    double totalRating;   // Sum of ratings
public:
    Game();
    Game(string n, int minP, int maxP, int minT, int maxT, int year, double r, bool borrowed);
    // Student A ToDo: Add Getters/Setters for all attributes

    // Getters
    string getName();
    int getMinPlayers();
    int getMaxPlayers();
    int getMinPlaytime();
    int getMaxPlaytime();
    int getYearPublished();
    double getAvgRating();
    bool getIsBorrowed();

    // Setters
    void setName(string n);
    void setMinPlayers(int p);
    void setMaxPlayers(int p);
    void setMinPlaytime(int t);
    void setMaxPlaytime(int t);
    void setYearPublished(int y);
    void setIsBorrowed(bool status);

    // Rating functions
    void addRating(int score);
    void display();
};

// Student A ToDo: Implement a manual Linked List to store Game objects
struct GameNode {
    Game data;
    GameNode* next;
};

class GameList {
private:
    GameNode* head;
    int size;
public:
    GameList();
    ~GameList();
    void add(Game g);
    void remove(string name);
    // Student A ToDo: Find a game by name (Linear Search)
    Game* find(string name);
    Game* findAvailableCopy(string name); // Find first available copy
    Game* findBorrowedCopy(string name);  // Find first borrowed copy
};
#endif