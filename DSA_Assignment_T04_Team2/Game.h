#ifndef GAME_H
#define GAME_H
#include <string>
#include <iostream>
using namespace std;


const int MAX_PLAYERS = 6;  //New
const int MAX_RECORDS = 200; //New

const int MAX_REVIEWS = 1000;

struct Review {
    string memberID;
    string memberName;
    int rating;
    string comment;
};

class Game {
private:
    string borrowDate;
    string returnDate;
    string name;
    int minPlayers, maxPlayers, minPlaytime, maxPlaytime, yearPublished;
    double avgRating;
    bool isBorrowed;
    int ratingCount;      // Number of ratings
    double totalRating;   // Sum of ratings
    Review reviews[MAX_REVIEWS];
    int reviewCount;
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
    bool getIsBorrowed() const;
    string getBorrowDate() const { return borrowDate; }
    string getReturnDate() const { return returnDate; }
    int getReviewCount() const { return reviewCount; }
    Review getReview(int index) const { return reviews[index]; }

    // Setters
    void setName(string n);
    void setMinPlayers(int p);
    void setMaxPlayers(int p);
    void setMinPlaytime(int t);
    void setMaxPlaytime(int t);
    void setYearPublished(int y);
    void setIsBorrowed(bool status);
    void setBorrowDate(string date) { borrowDate = date; }
    void setReturnDate(string date) { returnDate = date; }

    // Rating functions
    void addRating(int score);
    void display();

    //Review functions
    void addReview(const string& mID, const string& mName, int rating, const string& comment);
    void displayReviews() const;
};

class GameNode {
public:
    Game data;
    GameNode* next;

    GameNode(const Game& g) : data(g), next(nullptr) {}
};

// Student A ToDo: Implement a manual Linked List to store Game objects
//struct GameNode {
//    Game data;
//    GameNode* next;
//    GameNode(Game g);
//};

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
    GameNode* get();
};

//Newly Added
struct GamePlayRecord {
    string gameName;
    string players[MAX_PLAYERS];
    int playerCount;
    string winnerID;
};

struct HistoryNode {
    GamePlayRecord data;
    HistoryNode* next;
};
class GameHistory {
private:
    GamePlayRecord records[MAX_RECORDS];
    int recordCount;
    HistoryNode* head;

public:
    GameHistory();
    ~GameHistory();
    void addRecord(GamePlayRecord r);
    void displayAll();
    void searchByGame(string gameName);
    void bubbleSortByGame();
    HistoryNode* getHead() { return head; }
};


#endif