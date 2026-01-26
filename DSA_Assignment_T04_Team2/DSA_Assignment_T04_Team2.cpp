// DSA_Assignment_T04_Team2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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


