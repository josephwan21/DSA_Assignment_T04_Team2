#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include <vector>
using namespace std;

class Member {
private:
    string memberID;
    string name;
    vector<string> borrowedGames;
    // Student A ToDo: A simple array or list to store borrowed game names
public:
    Member();
    Member(string id, string n);
    string getID();
    string getName();
    void borrowGame(string gameName);
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
};
#endif