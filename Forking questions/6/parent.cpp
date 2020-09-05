#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string>
using namespace std;

int main(int argc, char *argv[])
{   
  int n;n= stoi(argv[1]);
  pid_t p=fork();
  if(p==0)
  {
  char *args[n+2];
  args[0]=argv[1];
  for(int i=1;i<n+2;i++)
  {
    args[i]=argv[i+1];
  }
  args[n+1]=NULL;
  execv("./child",args);
  }
else{
  wait(NULL);
  int a[100];int j=0;

  for(int i=2;j<n;i++)
  {
    a[j]= stoi(argv[i]);
    j++;
  }
  
for (int i = n/2; i < n; i++)                 //Loop for Descending ordering
  {
    for (int j = n/2; j < n; j++)             //Loop for comparing other values
    {
      if (a[j] < a[i])                      //Comparing other array elements
      {
        int tmp = a[i];                     //Using temporary variable for storing last value
        a[i] = a[j];                        //replacing value
        a[j] = tmp;                         //storing last value
      }  
    }
  }
  printf("Descending :\n");                     //Printing message
  for (int i = n/2; i < n; i++)                     //Loop for printing array data after sorting
  {
    printf(" %d ", a[i]);
  }
  printf("\n");
}
  return 0;
}





