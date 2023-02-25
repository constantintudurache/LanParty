#include "functions.hpp"
#include "player.hpp"
#include "team.hpp"


int main(int argc, char* argv[])
{
    
    ///argv[0] = lanParty -> numele executabilului
    ///argv[1] = c.in
    ///argv[2] = d.in
    ///argv[3] = r.out

    ifstream task (argv[1]);
    ifstream input (argv[2]);
    ofstream output (argv[3]);

    int taskNo, teamsNo = 0;  
    char buf[256];
    Player player;
    Team team;

    taskNo = setTask(task);

    switch(taskNo){
    case 1:{
            input >> teamsNo;
            input.get();
            list<Team> head;
            head = generateList(input,teamsNo);
            printList(head,output);

        }break;

    case 2:{
            list<Team> head;
            head = chooseTeams(input,output);
            printList(head,output);
        }break;

    case 3:{
            list<Team> head;
            head = chooseTeams(input,output);
            queue<Team> matches, top8;
            tournament(output,head,top8);
        }break;
        
    case 4:{
            list<Team> head;
            head = chooseTeams(input,output);
            queue<Team> matches, top8;
            tournament(output,head,top8);
            printTop8(output,top8);
        }break;
    }

    task.close();
    input.close();
    output.close();
    
    return 0;
}
