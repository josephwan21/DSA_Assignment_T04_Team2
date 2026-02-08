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

#include "Member.h"
#include <iostream>
using namespace std;

string toUpperCase(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = s[i] - 'a' + 'A';
        }
    }
    return s;
}

Member::Member() {
    memberID = "";
    name = "";
    borrowedCount = 0;
    for (int i = 0; i < MAX_BORROWED; i++)
        borrowedGames[i] = "";
}

Member::Member(string id, string n) {
    memberID = id;
    name = n;
    borrowedCount = 0;
    for (int i = 0; i < MAX_BORROWED; i++)
        borrowedGames[i] = "";
}

string Member::getID() {
    return memberID;
}

string Member::getName() {
    return name;
}

void Member::borrowGame(string gameName) {
    if (borrowedCount < MAX_BORROWED) {
        borrowedGames[borrowedCount] = gameName;
        borrowedCount++;
    }
}

// --- MemberHash Implementation (Data Structure 2: Hash Table) ---

MemberHash::MemberHash() 
{
    for (int i = 0; i < MAX_SIZE; i++) 
        table[i] = nullptr;
}

// Student A ToDo: Implement a hash function (e.g., sum of ASCII % MAX_SIZE)
int MemberHash::hashFunction(string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return sum % MAX_SIZE;
}

// Student A ToDo: Add Member to table (Handle collisions using Linked List/Chaining)
void MemberHash::addMember(Member m) {
    int index = hashFunction(m.getID());

    HashNode* newNode = new HashNode;
    newNode->key = m.getID();
    newNode->member = m;
    newNode->next = table[index];  // insert at head

    table[index] = newNode;
}

// Student A ToDo: Retrieve a member pointer using their ID
Member* MemberHash::getMember(string id) {
    id = toUpperCase(id);
    int index = hashFunction(id);
    HashNode* temp = table[index];

    while (temp != nullptr) {
        if (temp->key == id) {
            return &(temp->member);
        }
        temp = temp->next;
    }
    return nullptr; //if member not found
}

// Remove a game from borrowed list
void Member::returnGame(string gameName) {
    for (int i = 0; i < borrowedCount; i++) {
        if (borrowedGames[i] == gameName) {
            // Shift left
            for (int j = i; j < borrowedCount - 1; j++) {
                borrowedGames[j] = borrowedGames[j + 1];
            }
            borrowedCount--;
            return;
        }
    }
}

// Display borrowed games
void Member::displayBorrowedGames() {
    if (borrowedCount == 0) {
        cout << "No games currently borrowed.\n";
        return;
    }

    cout << "Borrowed Games:\n";
    for (int i = 0; i < borrowedCount; i++) {
        cout << "- " << borrowedGames[i] << endl;
    }
}