#ifndef FCT_HPP
#define FCT_HPP

#include "team.hpp"

void isNULL(void*);

char* charAlloc(int);

char* setChar(char[]);

int setTask(ifstream&);

void generatePlayer(char[], Player&);

void generateTeamName(ifstream&, Team&);

Team setTeam(ifstream&);

void printList(list<Team>&,ofstream&);

list<Team> generateList(ifstream&,int);

int setTeamsNumber(int);

float findMin(list<Team>);

list<Team> chooseTeams(ifstream&, ofstream&);

queue<Team> generateQueue(list<Team>);

queue<Team> generateQueue(stack<Team>);

void printQueue(queue<Team>,ofstream&);

void Round(queue<Team>, stack<Team>&,stack<Team>&);

void printStack(stack<Team>, ofstream&);

void printRounds(ofstream&, queue<Team>, int);

void printWinners(ofstream&,stack<Team>&, int, queue<Team>&);

void printTop8(ofstream&,queue<Team>);

void tournament(ofstream&, list<Team>, queue<Team>&);

int getMaxIndex(queue<Team>&, int);

void insertMaxToRear(queue<Team>&, int);

void sortQueue(queue<Team>&);

#endif