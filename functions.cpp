#include "functions.hpp"

void isNULL(void* ptr){
    if(ptr == NULL){
        cout << "alocare esuata";
        exit(1);
    }
}

char* charAlloc(int lenght){
    char* str = NULL;
    str = new char[lenght+1];
    isNULL(str);
    return str;
}

char* setChar(char buf[]){
    char* str = NULL;
    str = charAlloc(strlen(buf));
    strcpy(str,buf);
    return str;
}

int setTask(ifstream& task){
    int value = 0, aux ;
    while(task >> aux)
        value += aux;
    return value;
}



void generatePlayer(char buf[], Player &player){
    char *p = NULL;
    int pts = 0;
    p = strtok(buf," ");
    player.setSecondName(p,strlen(p)+1);
    p = strtok(NULL," ");
    player.setFirstName(p, strlen(p)+1);
    p = strtok(NULL," ");
    player.setPoints(atoi(p));
}


void generateTeamName(ifstream& input, Team &team){
    char buf[256], nameBuf[256], *p;
    int capacity;
    input >> capacity;
    team.setCapacity(capacity);
    input.getline(buf,256);
    strcpy(buf, buf+1);
    strcpy(nameBuf,"");
    p = strtok(buf, " ");
    while(p){
        strcat(nameBuf,p);
        strcat(nameBuf," ");
        p = strtok(NULL, " ");
    }
     nameBuf[strlen(nameBuf)-1] = '\0';
     team.setTeamName(nameBuf, strlen(nameBuf)+1);

}

Team setTeam(ifstream& input){

    int i;
    Team team;
    Player player;
    char buf[256];
    float sum = 0;
    generateTeamName(input,team);
    team.allocMembers(team.getCapacity());
    strcpy(buf,"");
    
    for(i = 0; i < team.getCapacity(); i++){
        
        input.getline(buf,256); 
        generatePlayer(buf,player);
        team.insertMembers(i,player);
        sum += team.getMembers(i).getPoints();
        
    }
    sum /= (1.*team.getCapacity());
    team.setTeamPoints(sum);
    
    return team;
}

void printList(list<Team> &head, ofstream& output) {

    list<Team>::iterator itr;
    Team team;

    for(itr = head.begin(); itr != head.end(); itr++ ) {

        output << *itr << endl;
        team = *itr;
    }

    head.clear();

}

list<Team> generateList(ifstream& input, int teamsNo) {

    list<Team> head;
    Team team;
   
    for (int i = 0; i < teamsNo; i++) {

       input >> team;
       head.emplace_front(team);

    }

    return head;
}

int setTeamsNumber(int teamsNo){
    int value = 1;
    teamsNo = log2(teamsNo);
    value <<= teamsNo;
    return value;
}

float findMin(list<Team> head){

    float minValue = FLT_MAX;
    list<Team>::iterator x;
    for(x = head.begin(); x != head.end(); x++){
        if(x->getTeamPoints() < minValue){
             minValue = x->getTeamPoints();
        }
           
    }
    return minValue;
}

list<Team> chooseTeams(ifstream& input, ofstream& output){
    list<Team> head;
    list<Team>::iterator itr;
    Team team;
    int teamsNo;
    input >> teamsNo;
    input.get();
    head = generateList(input,teamsNo);
    int counter = 0;
    float minValue;
    while(counter <  teamsNo - setTeamsNumber(teamsNo)){
        minValue = findMin(head);
        for(itr = head.begin(); itr !=head.end(); itr++){
           if(itr->getTeamPoints() == minValue){
                head.erase(itr);
                break;
           }  
        }
        counter++;
    }
    return head;
}

queue<Team> generateQueue(list<Team> head){
    queue<Team> matches;
    for(auto i = head.begin(); i != head.end(); i++)
        matches.push(*i);

    return matches;
}

queue<Team> generateQueue(stack<Team> winners){
    queue<Team> matches;

    while(!winners.empty()){
        matches.push(winners.top());
        winners.pop();
    }

    return matches;
}

void printQueue(queue<Team> Queue, ofstream& output){
    
    while (!Queue.empty()){

        output << Queue.front() << endl;
        Queue.pop();
    }
    cout << endl;
}

void Round(queue<Team> Queue, stack<Team> &winners, stack<Team> &losers){
    Team team1, team2;
    while(!Queue.empty()){
        team1 = Queue.front();
        Queue.pop();
        team2 = Queue.front();
        Queue.pop();
        if(team1.getTeamPoints() > team2.getTeamPoints()){
            team1.win();
            winners.push(team1);
            losers.push(team2);
        }
        else{
                team2.win();
                winners.push(team2);
                losers.push(team1);
            }
    }
    
}

void printStack(stack<Team> Stack, ofstream& output){
   Team team;
   
    while(!Stack.empty()){
        cout << Stack.top().getTeamName() << endl;
        output << Stack.top().getTeamName() << endl;
        team = Stack.top();
        Stack.pop(); 
    }
    cout << endl;
}

void printRounds(ofstream& output, queue<Team> Queue, int roundIndex){
    
    int lenght1;
    output << " --- ROUND NO:" << roundIndex << endl;
    while(!Queue.empty()){
        output << Queue.front();
        lenght1 = strlen(Queue.front().getTeamName());
        Queue.pop();
        for(auto i = lenght1; i < 66 - strlen(Queue.front().getTeamName()); i++){
            if(i == 33)
                output << '-';
            else
            output << ' ';
        }
        output << Queue.front() << endl;
        Queue.pop();
    }
    output << endl;
}

void printWinners(ofstream& output, stack<Team> &winners, int roundIndex,  queue<Team> &Queue){
    output << "WINNERS OF ROUND NO:" << roundIndex << endl;
    queue<Team> auxQueue;
    while(!winners.empty()){
        output << winners.top();
        for(auto i = strlen(winners.top().getTeamName()); i < 35;  i++){
            if(i == 33)
            output << '-';
            else
            output <<' ';
        }
        output << setprecision(3) << winners.top().getTeamPoints() << endl;
        auxQueue.push(winners.top());
        winners.pop();
    }
    Queue = auxQueue;
    output << endl;
}

void printTop8(ofstream &output, queue<Team> top8){

    if(!top8.empty())
        sortQueue(top8);
        
    if(!top8.empty())
        sortQueue(top8);
   

    output << "TOP 8 TEAMS:" << endl;

    while (!top8.empty()){

        output << top8.front();
        for(auto i = strlen(top8.front().getTeamName()); i <= 35 ; i++){
            if(i == 34)
                output <<'-';
            else
            output<<' ';
        }
        output << setprecision(3) << top8.front().getTeamPoints() << endl;
        top8.pop();
    }
    output << endl;
}

void tournament(ofstream& output, list<Team> teamList, queue<Team> &top8){
    int roundIndex = 1;
    queue<Team> Queue;

    Queue = generateQueue(teamList);
    printQueue(Queue, output);
    output << endl;

    stack<Team> winners, losers;

    while(!Queue.empty()){

        Round(Queue,winners,losers);
        
        if(winners.size() == 8){
            top8 = generateQueue(winners);  
        }

        printRounds(output,Queue,roundIndex);
        printWinners(output,winners,roundIndex,Queue);
        roundIndex++;

        if(Queue.size() == 1)
            break;
    }
}

int getMaxIndex(queue<Team> &top8, int sortedIndex) {
    int max_index = -1;
    float max_val = FLT_MIN;

    int n = top8.size();
    Team previous(top8.front());

    for (int i = 0; i < n; i++)
    {
        Team current = top8.front();
        top8.pop();

        if ((current.getTeamPoints() > max_val && i <= sortedIndex) || (current.getTeamPoints() == max_val && i <= sortedIndex && strcmp(current.getTeamName(), previous.getTeamName()) > 0)) {
            max_index = i;
            max_val = current.getTeamPoints();
        }

        top8.push(current);
        Team previous(current);
    }

    return max_index;
}

void insertMaxToRear(queue<Team> &top8, int max_index) {
    Team max_val;
    int n = top8.size();

    for (int i = 0; i < n; i++) {
        Team current = top8.front();
        top8.pop();
        if (i != max_index)
            top8.push(current);
        else
            max_val = current;
    }
    top8.push(max_val);
}

void sortQueue(queue<Team> &top8) {
    for (int i = 1; i <= top8.size(); i++) {
        int max_index = getMaxIndex(top8, top8.size() - i);
        insertMaxToRear(top8, max_index);
    }
}