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