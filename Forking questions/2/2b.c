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
  int sumodd=0,sumeven=0;

  pid = fork();
  if (pid == 0)
    {
      for(i=1;i<=n;i++)
        if(i%2 == 0)
          sumeven+=i;

      if(i==n+1)
        printf("Sum of even numbers= %d\n",sumeven);
    }
  else
    {
      if (pid > 0)
        pid = waitpid(pid, &status, 0);
      for(i=1;i<=n;i++)
        if(i%2 != 0)
          sumodd+=i;
      if(i==n+1)
        printf("Sum of odd numbers= %d\n",sumodd);
    }
  return 0;
}

