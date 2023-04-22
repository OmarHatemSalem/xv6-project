#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf(2, "Please enter PID and new priority\n");
    } else {
        if (set_priority(atoi(argv[1]), atoi(argv[2])) > -1)
            printf(1, "Process [%d] now has priority %d\n", atoi(argv[1]), atoi(argv[2]));
        else if (set_priority(atoi(argv[1]), atoi(argv[2])) == -1)
            printf(2, "Please input valid PID\n");
        else
            printf(2, "Please input valid priority\n");

    }

    exit();
} 