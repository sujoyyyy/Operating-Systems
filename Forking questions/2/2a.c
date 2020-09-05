#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() 
{
  int i; //iterator
  int n; //range
  int status;
  printf("Enter n\n");
  scanf("%d",&n);
  pid_t pid;

  pid = fork();
  if (pid == 0)
    {
      for(i=1;i<=n;i++)
        if(i%2 == 0)
          printf("even %d\n",i);
    }
  else
    {
      if (pid > 0)
        pid = waitpid(pid, &status, 0);
      for(i=1;i<n;i++)
        if(i%2 != 0)
          printf("odd %d\n",i);
    }
  return 0;
}

