#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  //pipe yang mempunyai 2 ujung, p[1] atas, p[0] bawah 
  int p[2];
  pipe(p);
  int pid = fork();

  if (pid == 0) // parent
    {
      // p[0] read
      dup2(p[0], 0);
      close(p[1]);
      char *argv[] = {"wc", "-l", NULL};
      execv("/usr/bin/wc", argv);
    }
  else //child
    { 
      //p[0] write
      dup2(p[1], 1);
      close(p[0]);
      char *argv[] = {"ls", NULL};
      execv("/bin/ls", argv);
    }
}