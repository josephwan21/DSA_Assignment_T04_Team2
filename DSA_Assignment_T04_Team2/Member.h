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
    // Student A ToDo: A simple array or list to store borrowed game names
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
    // Student A ToDo: Add/Get members using hashing logic
    void addMember(Member m);
    Member* getMember(string id);
    HashNode** getTable() {
        return table;
    }
};
#endif