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
  printf("Enter range\n");
  scanf("%d",&n);
  pid_t pid;
  
  for(int i=1;i<=n;i++)
  {
  
  pid = vfork();
  int sum=0;int k=i;
  if (pid == 0)
    {
        while(k!=0)
        {
          int t= k%10;
          sum+=t*t*t;
          k=k/10;
        }
       pid=1;
    }
      if (pid > 0)
      { pid = waitpid(pid, &status, 0);
        if(sum==i)
        printf("Armstrong number = %d\n",i);
      }
    
  }
  exit(0);
  return 0;
}

