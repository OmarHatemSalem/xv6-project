#include "types.h"
#include "stat.h"
#include "user.h"
#include "date.h"

int isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        // if (!isdigit(number[i]))
        if (number[i] > '9' || number[i] < '0')
            return 0;
    }
    return 1;
}


int CalcDays(int iMonth, int iDay, int iYear)
{
    return (iDay + (153 * (iMonth + 12 * ((14 - iMonth) / 12) - 3) + 2) / 5 + 365 *
        (iYear + 4800 - ((14 - iMonth) / 12)) + (iYear + 4800 - ((14 - iMonth) / 12)) / 4 - 32083);
}


int
main(int argc, char *argv[])
{
    struct rtcdate dt;
    // getali()
    date(&dt);

    if (argc < 3)
    {
    printf(2,"Insufficient Funds... \n");
    exit();
    /* code */
    }

    if (!isNumber(argv[1]) || !isNumber(argv[2])) {
        printf(2, "Entires must be an integer\n");
        exit();
      }

    int lowerBound = atoi(argv[1]);
    int upperBound = atoi(argv[2]);

    if (lowerBound > upperBound) {
        printf(2, "Lower Bound cannot be greater than upper bound.\n");
        exit();
    }

    int seed = dt.year + dt.day+ dt.month + dt.hour + dt.minute + dt.second;
    int rand = ((seed * 214013 + 2531011) >> 16) & 0x7fff; 
    int rand2 = ((rand * 214013 + 2531011) >> 16) & 0x7fff;
    printf(1,"Random Number: %d\n",rand2 % (upperBound - lowerBound) + lowerBound);


    exit();
}


