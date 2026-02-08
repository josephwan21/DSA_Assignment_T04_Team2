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
- Additional Feature: Allow members to record play of a game + other members who played the game and who won the game + Search game history and Sort game history
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

#include "Member.h"
#include <iostream>
using namespace std;

/*
Function: toUpperCase - Helper Function
Description: Converts a string to uppercase (used for case-insensitive lookups).
Input: string s - the string to convert.
Return: string - the uppercase version of the input string.
*/
string toUpperCase(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = s[i] - 'a' + 'A';
        }
    }
    return s;
}

//Constructors
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

/*
Function: getID
Description: Retrieves the member's ID.
Input: none
Return: string - the member's ID
*/
string Member::getID() {
    return memberID;
}

/*
Function: getName
Description: Retrieves the member's name.
Input: none
Return: string - the member's name
*/
string Member::getName() {
    return name;
}

/*
Function: borrowGame
Description: Adds a game to the member's borrowed list if there is space.
Input: string gameName - name of the game to borrow
Return: void
*/
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

// Joseph ToDo: Implement a hash function (e.g., sum of ASCII % MAX_SIZE)
/*
Function: hashFunction
Description: Computes a hash index for a given member ID using sum-of-ASCII % table size.
Input: string key - member ID
Return: int - index in the hash table
*/
int MemberHash::hashFunction(string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return sum % MAX_SIZE;
}

// Joseph ToDo: Add Member to table (Handle collisions using Linked List/Chaining)
/*
Function: addMember
Description: Adds a member to the hash table, handling collisions via chaining.
Input: Member m - the member object to add
Return: void
*/
void MemberHash::addMember(Member m) {
    int index = hashFunction(m.getID());

    HashNode* newNode = new HashNode;
    newNode->key = m.getID();
    newNode->member = m;
    newNode->next = table[index];  // insert at head

    table[index] = newNode;
}

// Joseph ToDo: Retrieve a member pointer using their ID
/*
Function: getMember
Description: Retrieves a pointer to a member from the hash table by ID (case-insensitive).
Input: string id - the member ID to search for
Return: Member* - pointer to the member if found, nullptr otherwise
*/
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

/*
Function: returnGame
Description: Removes a game from the member's borrowed list.
Input: string gameName - name of the game to return
Return: void
*/
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
/*
Function: displayBorrowedGames
Description: Prints the list of currently borrowed games.
Input: none
Return: void
*/

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