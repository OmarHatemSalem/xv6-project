#include "types.h"
#include "stat.h"
#include "user.h"



int main(int argc, char* argv[]) {

    
    printf(1, "I am the parent, PID: %d\n", getpid());
    int new_child = fork();

    if (new_child == 0) {
        printf(1, "I am the child, PID: %d\n", getpid());
    }

    exit();
}

