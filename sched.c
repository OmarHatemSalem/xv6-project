#include "types.h"
#include "stat.h"
#include "user.h"

char* argv[] = {"ps", 0};

int main(){
    
    exec("ps",argv);
    set_priority(getpid(), 16);
    exec("ps", argv);
    // if(fork() == 0){
    //     exec("ps", argv);
    //     set_priority(getpid(),16);
    //     printf(1,"Hello from child\n");
    // }
    // else{
    //     printf(1, "Hello from parent\n");
    //     exec("ps", argv);

    // }

    exit();

}