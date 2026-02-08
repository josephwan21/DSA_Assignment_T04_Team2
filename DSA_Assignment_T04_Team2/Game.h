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

#ifndef GAME_H
#define GAME_H
#include <string>
#include <iostream>
using namespace std;


const int MAX_PLAYERS = 6;  //New
const int MAX_RECORDS = 200; //New

const int MAX_REVIEWS = 10;

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
    int findReviewIndexByMember(const string& memberID) const;
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
    void add(const Game& g);
    void remove(string name);
    // Student A ToDo: Find a game by name (Linear Search)
    Game* find(string name);
    Game* findAvailableCopy(string name); // Find first available copy
    Game* findBorrowedCopy(string name);  // Find first borrowed copy
    GameNode* get();
};

// --- Nigel Advanced Features---
//Newly Added Classes and Structs 

/*
 * Struct: GamePlayRecord
 * Description: Stores information about a single gameplay session.
 */
struct GamePlayRecord {
    string gameName;
    string players[MAX_PLAYERS];
    int playerCount;
    string winnerID;
};

/*
 * Struct: HistoryNode
 * Description: Node structure for the linked list used in GameHistory.
 */
struct HistoryNode {
    GamePlayRecord data;
    HistoryNode* next;
};


/*
 * Class: GameHistory
 * Description:
 * Manages the history of played games using a linked list.
 * Supports adding, searching, sorting, and displaying records.
 */
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