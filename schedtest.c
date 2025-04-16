#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char * argv[]){
    int i;
    int pscalls = atoi(argv[1]);
    int tickets[pscalls];
    int pids[pscalls];

    if(argc < 2){
        printf(1, "schedtest loops tickets1 [tickets2, ... ticketsN]\n \
            loops must be greater than 0\n \
            tickets must be greater than or equal to 10\n \
            up to 7 tickets can be provided\n");
        exit();
    }

    //set tickets from args
    for(i = 0; i < argc - 2; i++){
        tickets[i] = atoi(argv[i + 2]);
    }

    //for number of desired loops, 
    //make processes and set specific processes new amount of tickets
    //log pids
    for(i = 0; i < pscalls; i++){
        int pid = fork();
        if(pid == 0){
            settickets(tickets[i]);
            while(1){}
            exit();
        }
        else{
            pids[i] = pid;
        }
    }

    //ps for number of loops
    for(i = 0; i < pscalls; i++){
        ps();
        sleep(3);
    }

    //kill created processes (children)
    for(i = 0; i < pscalls; i++){
        kill(pids[i]);
    }

    //reap child processes
    for(i = 0; i < pscalls; i++){
        wait();
    }

    //parent can exit
    exit();
}