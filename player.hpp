#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <cmath>
#include <cfloat>
#include <cstring>
#include <fstream>
#include <limits>
#include <list>
#include <queue>
#include <stack>
#include <iomanip>
#include <cstdio>

using namespace std;


 class Player{
    char *firstName;
    char *secondName;
    int points;
     
    public:
    Player();
    Player(char*, char*, int);
    Player(const Player&);
    ~Player();
    void swapPlayers(Player&,Player&);
    char* allocName(int);
    void setFirstName(char*, int);
    void setSecondName(char*, int);
    void setPoints(int);
    char* getFirstName();
    char* getSecondName();
    int getPoints();
    friend istream& operator>>(istream&, Player&);
    friend ostream& operator<<(ostream&, Player&);
    };





#endif