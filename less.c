#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
less(int fd)
{
  int n;

  // ftruncate(fd);


  // for (int i=0; i<10; i++) {
  //   n = read(fd, buf, sizeof(buf));
  //   if (write(1, buf, n) != n) {
  //     printf(1, "less: write error\n");
  //     exit();
  //   }
  // }

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (ftruncate(1, buf, n) != n) {
      // printf(1, "less: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "less: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    less(0);
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "less: cannot open %s\n", argv[i]);
      exit();
    }
    less(fd);
    close(fd);
  }
  exit();
}
