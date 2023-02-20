#include "types.h"
#include "stat.h"
#include "user.h" 

int validateNumber(char* str);


int main(int argc, char *argv[])
{
  printf(1, "Number of arguments: %d\n", argc-1);
  printf(1, "Target: %s\n", argv[1]);
  int target, number;
  for(int i=1; i<argc; i++)
  {
    if(!validateNumber(argv[i]))
    {
        printf(2, "Invalid number: %s\n", argv[i]);
        exit();
    }
    if(i == 1) {
        if (argv[i][0] == '-') target = -1*atoi(argv[i]+1);
        else target = atoi(argv[i]);
    }
    else
    {   
        if (argv[i][0] == '-') number = -1*atoi(argv[i]+1);
        else number = atoi(argv[i]);


        if(number == target)
        {
            printf(1, "Found target at index %d of the array\n", i-2);
            exit();
        }
    }
  }
  printf(1, "Target not found\n");
  exit();
}

int validateNumber(char* str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        if (i==0 && str[i]=='-') {i++; continue;}
        

        if(str[i] < '0' || str[i] > '9' )
        {
        return 0;
        }
        i++;
    }
    return 1;
}