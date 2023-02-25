#include "team.hpp"

void Team::swapTeams(Team& team1, Team& team2){
    team1.teamCapacity +=team2.teamCapacity;
    team2.teamCapacity = team1.teamCapacity - team2.teamCapacity;
    team1.teamCapacity = team1.teamCapacity - team2.teamCapacity;

    team1.teamPoints +=team2.teamPoints;
    team2.teamPoints = team1.teamPoints - team2.teamPoints;
    team1.teamPoints = team1.teamPoints - team2.teamPoints;

    char *aux;
    aux = new char[strlen(team2.teamName)+1];
    strcpy(aux,team2.teamName);
    delete [] team2.teamName;
    team2.teamName = new char[strlen(team1.teamName)+1];
    strcpy(team2.teamName,team1.teamName);
    delete [] team1.teamName;
    team1.teamName = aux;



}

char* Team::allocName(int capacity){
    return new char[capacity];
}
Team::Team() :teamCapacity(0), teamPoints(0.0), teamName(NULL), members(NULL){

}

Team::Team(int capacity, float points, char* name, Player* membersAdr){
    teamCapacity = capacity;
    teamPoints = points;
    strcpy(teamName,name);
    members = membersAdr;
}

Team::Team(const Team& team){
    teamCapacity = team.teamCapacity;
    teamPoints = team.teamPoints;
    teamName = new char[strlen(team.teamName)+1];
    strcpy(teamName,team.teamName);
    members = new Player[teamCapacity];
    for(int i = 0; i < teamCapacity; i++){
        members[i].setFirstName(team.members[i].getFirstName(), strlen(team.members[i].getFirstName()));
        members[i].setSecondName(team.members[i].getSecondName(), strlen(team.members[i].getSecondName()));
        members[i].setPoints(team.members[i].getPoints());
    }
}

Team :: ~Team() {

    if(this->teamName != NULL)
        delete [] teamName;
    
    if(this->members)
        delete [] members;

}

void Team::setCapacity(int value){
    teamCapacity = value;
}

int Team::getCapacity(){
    return teamCapacity;
}

void Team::setTeamPoints(float value){
    teamPoints = value;
}

float Team::getTeamPoints(){
    return teamPoints;
}

void Team::setTeamName(char *name, int capacity){
    teamName = allocName(capacity);
    strcpy(teamName,name);
}

char* Team::getTeamName(){
    return teamName;
}

void Team::allocMembers(int capacity){
    members =  new Player[capacity]; 
}

void Team::insertMembers(int position, Player value){
    members[position] = value;
}

void Team::win() {
    
    for(int i = 0; i < this->teamCapacity; i++){

        this->members[i].setPoints(this->members[i].getPoints() + 1);

    }

    this->teamPoints++;
    
}

Player Team::getMembers(int position){
    return members[position];
}

istream& operator>>(istream& input, Team& obj) {

    char buf[256], *p;
    Player player;
    float sum = 0;

    input.getline(buf, 256);

    p = strtok(buf, " ");
    obj.setCapacity(atoi(buf));

    p = strtok(NULL, "\n");
    obj.setTeamName(p, strlen(p));

    obj.allocMembers(obj.getCapacity());

    for(int i = 0; i < obj.getCapacity(); i++) {

        input >> player;
        obj.insertMembers(i, player);
        sum += 1.0 * player.getPoints();
    }
    
    obj.setTeamPoints(sum / obj.getCapacity());

    input.get();

    return input;

}

ostream& operator<<(ostream& output, Team& obj){

        output << obj.getTeamName();

        return output;
}