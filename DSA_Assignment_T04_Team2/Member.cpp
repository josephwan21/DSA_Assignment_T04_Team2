#include "Member.h"

Member::Member(string id, string n) : memberID(id), name(n) {}

// --- MemberHash Implementation (Data Structure 2: Hash Table) ---

MemberHash::MemberHash() {
    for (int i = 0; i < MAX_SIZE; i++) table[i] = nullptr;
}

// Student A ToDo: Implement a hash function (e.g., sum of ASCII % MAX_SIZE)
int MemberHash::hashFunction(string key) {
    return 0; // Placeholder
}

// Student A ToDo: Add Member to table (Handle collisions using Linked List/Chaining)
void MemberHash::addMember(Member m) {
    // Get index from hashFunction, create node, add to table[index]
}

// Student A ToDo: Retrieve a member pointer using their ID
Member* MemberHash::getMember(string id) {
    return nullptr; // Placeholder
}