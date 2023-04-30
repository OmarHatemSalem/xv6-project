#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int parent_pid = getpid();
    printf(1, "Starting long-running background process with pid: %d...\n", parent_pid);

    int child = 0;
    
    if(fork() == 0)
    {
        // first child done to be ignored due to low priority (starved)
        printf(1, "CHILD 1: INSIDE CHILDE: Child process started with pid: %d\n", getpid());
        set_priority(getpid(), 1);
        printf(1, "CHILD 1: CHANGED PRI: Child process with pid: %d has priority: %d\n", getpid(), 1);
        for(int z = 0; z < 400000; z+=1)
        {
            int x = 0;
            x = x + 3.14*89.64; //Useless calculation to consume CPU Time
            yield();
        }
        printf(1, "CHILD 1: FINISHED: Child process with pid: %d has finished\n", getpid());
        child = 1;
    }
    if(child == 0 && fork() == 0)
    {
        // first child done to be ignored due to low priority (starved)
        printf(1, "CHILD 2: INSIDE CHILDE: Child process started with pid: %d\n", getpid());
        set_priority(getpid(), 3);
        printf(1, "CHILD 2: CHANGED PRI: Child process with pid: %d has priority: %d\n", getpid(), 3);
        for(int z = 0; z < 400000; z+=1)
        {
            int x = 0;
            x = x + 3.14*89.64; //Useless calculation to consume CPU Time
            yield();
        }
        printf(1, "CHILD 2: FINISHED: Child process with pid: %d has finished\n", getpid());
        child = 1;
    }
    if(child == 0 && fork() == 0)
    {
        // first child done to be ignored due to low priority (starved)
        printf(1, "CHILD 3: INSIDE CHILDE: Child process started with pid: %d\n", getpid());
        set_priority(getpid(), 15);
        printf(1, "CHILD 3: CHANGED PRI: Child process with pid: %d has priority: %d\n", getpid(), 5);
        for(int z = 0; z < 400000; z+=1)
        {
            int x = 0;
            x = x + 3.14*89.64; //Useless calculation to consume CPU Time
            yield();
        }
        printf(1, "CHILD 3: FINISHED: Child process with pid: %d has finished\n", getpid());
        child = 1;
    }
    if(child == 0 && fork() == 0)
    {
        // first child done to be ignored due to low priority (starved)
        printf(1, "CHILD 4: INSIDE CHILDE: Child process started with pid: %d\n", getpid());
        set_priority(getpid(), 8);
        printf(1, "CHILD 4: CHANGED PRI: Child process with pid: %d has priority: %d\n", getpid(), 8);
        for(int z = 0; z < 400000; z+=1)
        {
            int x = 0;
            x = x + 3.14*89.64; //Useless calculation to consume CPU Time
            yield();
        }
        printf(1, "CHILD 4: FINISHED: Child process with pid: %d has finished\n", getpid());
        child = 1;
    }
    
    if(child == 0) 
    {
        while(wait()>0);
        printf(1, "FINISHED: Parent process with pid: %d finished\n", parent_pid);
    }
    exit();
}