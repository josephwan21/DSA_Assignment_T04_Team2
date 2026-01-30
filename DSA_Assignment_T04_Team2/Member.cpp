#include "Member.h"

Member::Member() {
    memberID = "";
    name = "";
}

Member::Member(string id, string n) : memberID(id), name(n) {}

string Member::getID() {
    return memberID;
}

string Member::getName() {
    return name;
}

void Member::borrowGame(string gameName) {
    borrowedGames.push_back(gameName);
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