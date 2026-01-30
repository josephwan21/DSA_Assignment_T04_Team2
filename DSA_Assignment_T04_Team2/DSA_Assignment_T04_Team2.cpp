#include "ClubManager.h"
#include <iostream>
#include <string>
#include "ClubManager.h"

using namespace std;

int main()
{
    cout << "Hello World!\n";
    ClubManager cm;
    cm.loadData("games.csv");
}

    // Student C ToDo: Implement the Menu System
    // Choice 1: Administrator -> (Add Game, Remove Member, Summary)
    // Choice 2: Member -> (Borrow, Return, Rate, View History)
    // Choice 3: All Users -> (Search by player count, Sort by Year)

    return 0;
}