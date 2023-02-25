
#include "player.hpp"

Player::Player() :firstName(NULL), secondName(NULL), points(0){

}

Player::Player(char *first, char *second, int playerPoints){
    strcpy(firstName,first);
    strcpy(secondName,second);
    points = playerPoints;
}

Player::Player(const Player& player){
    points += player.points;
    firstName = new char[strlen(player.firstName)+1];
    secondName = new char[strlen(player.secondName)+1];
    strcpy(firstName,player.firstName);
    strcpy(secondName,player.secondName);
}

Player::~Player() {
    if(firstName != NULL)
        delete [] firstName;

    if(secondName != NULL)
        delete [] secondName;
}

void Player::swapPlayers(Player& player1, Player& player2){
    player1.points += player2.points;
    player2.points = player1.points - player2.points;
    player1.points = player1.points - player2.points;

    char *aux;

    aux = new char[strlen(player2.firstName)+1];
    strcpy(aux,player2.firstName);
    delete [] player2.firstName;
    player2.firstName = new char[strlen(player1.firstName)+1];
    strcpy(player2.firstName,player1.firstName);
    delete [] player1.firstName;
    player1.firstName = aux;

    aux = new char[strlen(player2.secondName)+1];
    strcpy(aux,player2.secondName);
    delete [] player2.secondName;
    player2.secondName = new char[strlen(player1.secondName)+1];
    strcpy(player2.secondName,player1.secondName);
    delete [] player1.secondName;
    player1.secondName = aux;

}


char* Player::allocName(int capacity){
    return new char[capacity];
}

void Player::setFirstName(char *value, int capacity){

    if(firstName != NULL)
        delete [] firstName;

    firstName = allocName(capacity);
    strcpy(firstName,value);

 }

void Player::setSecondName(char *value, int capacity){

    if(secondName != NULL)
        delete [] secondName;

    secondName = allocName(capacity);
    strcpy(secondName,value);

 }

void Player::setPoints(int value){
    points = value;
}

char* Player::getFirstName(){
    return firstName;
}

char* Player::getSecondName(){
    return secondName;
}

int Player::getPoints(){
    return points;
}

istream& operator>>(istream& input, Player& obj) {

    char buf[256], *p;

    input.getline(buf, 256);

    p = strtok(buf, " ");
    obj.setSecondName(p, strlen(p));

    p = strtok(NULL, " ");
    obj.setFirstName(p, strlen(p));

    p = strtok(NULL, " ");
    obj.setPoints(atoi(p));

    return input;

}

ostream& operator<<(ostream& output, Player& obj){

        output << obj.secondName << " " << obj.firstName << " " << obj.points << endl;

        return output;
}