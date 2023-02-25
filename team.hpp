#ifndef TEAM_HPP
#define TEAM_HPP

#include "player.hpp"

class Team{

private:

    int teamCapacity;
    float teamPoints;
    char *teamName;
    Player* members;

public:
    Team();
    Team(int,float,char*,Player*);
    Team(const Team&);
    ~Team();
    void swapTeams(Team&,Team&);
    char* allocName(int);
    void setCapacity(int);
    void setTeamPoints(float);
    void setTeamName(char*, int);
    void allocMembers(int);
    void insertMembers(int,Player);
    void win();
    int getCapacity();
    float getTeamPoints();
    char* getTeamName();
    Player getMembers(int);
    friend istream& operator>>(istream&, Team&);
    friend ostream& operator<<(ostream&, Team&);

};

#endif