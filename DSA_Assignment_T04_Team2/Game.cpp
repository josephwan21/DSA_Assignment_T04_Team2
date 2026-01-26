#include "Game.h"
#include <iostream>

// Student A ToDo: Constructor to initialize game details
Game::Game(string n, int minP, int maxP, int minT, int maxT, int year) 
{
    // Assign private variables here
}

// Student A ToDo: Display details of a single game (Requirement i)
void Game::display() 
{
    cout << "Game: " << name << " | Players: " << minPlayers << "-" << maxPlayers << endl;
}

// --- GameList Implementation (Data Structure 1: Linked List) ---

GameList::GameList() 
{ 
    head = nullptr; size = 0; 
}

// Student A ToDo: Insert a new GameNode at the end of the list
void GameList::add(Game g) 
{
    // Create new node, traverse to end, link it

}

// Student A ToDo: Linear Search to find a game by name
Game* GameList::find(string name) 
{
    // Traverse list and return pointer to Game if found
    return nullptr;
}

// Student A ToDo: Destructor to delete all nodes and prevent memory leaks
GameList::~GameList() 
{ 
    /* delete nodes */ 

}