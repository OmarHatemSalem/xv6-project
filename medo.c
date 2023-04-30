#include "types.h"
#include "stat.h"
#include "user.h"

char getc(int fd, char **buffer)
{
    int i = 0;
    char buf[256]; // read input into buffer
    while (read(fd, &buf[i], 1))
    {
        if ((buf[i] == '\n' || buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\r' || buf[i] == '\v' || buf[i] == '\f'))
            break;
        else
            i++;
    }
    buf[i] = '\0';
    *(buffer) = buf;
    return buf[0];
}



int main(int argc, char *argv[])
{
    printptable();
    printf(1, "press <q>/<Q> and return to exit\n");

    char *c;
    *c = getc(1, &c);
    while (*c != 'q' && *c != 'Q')
    {
        //clear screen
        printptable();
        printf(1, "press <q>/<Q> and return to exit\n");
        *c = getc(1, &c);
    }

    exit();
} 