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

#ifndef MEMBER_H
#define MEMBER_H
#include <string>
using namespace std;

const int MAX_BORROWED = 5;

class Member {
private:
    string memberID;
    string name;
    string borrowedGames[MAX_BORROWED];
    int borrowedCount;
    // Joseph ToDo: A simple array or list to store borrowed game names
public:
    Member();
    Member(string id, string n);
    string getID();
    string getName();
    void borrowGame(string gameName);
    void returnGame(string gameName);
    void displayBorrowedGames();
};

struct HashNode {
    string key; // memberID
    Member member;
    HashNode* next;
};

class MemberHash {
private:
    static const int MAX_SIZE = 101;
    HashNode* table[MAX_SIZE];
public:
    MemberHash();
    int hashFunction(string key);
    // Joseph ToDo: Add/Get members using hashing logic
    void addMember(Member m);
    Member* getMember(string id);
    HashNode** getTable() {
        return table;
    }
};
#endif