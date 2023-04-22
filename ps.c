#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

int validnumber(char *s);

int main(int argc, char *argv[])
{
  struct filtered_proc* p;
  if(argc == 1)
  {
    p = malloc(sizeof(struct filtered_proc));
    int processesIds[NPROC];
    int counter = 0;
    getprocs(processesIds, &counter);
    printf(1, "Number of Processes: %d\n", counter);
    for(int i=0; i<counter; i++)
    {
      getprocinfo(processesIds[i], p);
      printf(1, "pid: %d, parent id: %d, name: %s, size: %d, state: %s, priority: %d\n", p->pid, (p->parentpid>0 && p->parentpid<NPROC)?p->parentpid:0, p->name, p->sz, p->state,  p->priority);
    }
  }
  else if(argc == 2 && validnumber(argv[1]) && atoi(argv[1])>0)
  {
    p = malloc(sizeof(struct filtered_proc));
    int pid = atoi(argv[1]);
    if(getprocinfo(pid, p)>0)
      printf(1, "pid: %d, parent id: %d, name: %s, size: %d, state: %s, priority: %d\n", p->pid, (p->parentpid>0 && p->parentpid<NPROC)?p->parentpid:0, p->name, p->sz, p->state,  p->priority);
    else
      printf(2, "Error: Process with pid %d not found or unused\n", pid);
  }
  else
  {
    printf(2, "Error: Invalid arguments\n");
    printf(1, "Usage:\n");
    printf(1, "To list all processes: %s\n", argv[0]);
    printf(1, "OR\n");
    printf(1, "To list info about selected process: %s <pid>\n", argv[0]);
  }
  exit();
}

int validnumber(char *s)
{
  int i = 0;
  while(s[i] != '\0')
  {
    if(s[i] < '0' || s[i] > '9')
      return 0;
    i++;
  }
  return 1;
}