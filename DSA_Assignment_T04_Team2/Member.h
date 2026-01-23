#ifndef MEMBER_H
#define MEMBER_H
#include <string>
using namespace std;

class Member {
private:
    string memberID;
    string name;
    // Student A ToDo: A simple array or list to store borrowed game names
public:
    Member();
    Member(string id, string n);
    string getID();
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