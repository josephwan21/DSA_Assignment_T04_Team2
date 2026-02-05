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