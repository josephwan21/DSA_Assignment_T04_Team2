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
    // ... other attributes
public:
    Game();
    Game(string n, int minP, int maxP, int minT, int maxT, int year);
    // Student A ToDo: Add Getters/Setters for all attributes
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
};
#endif