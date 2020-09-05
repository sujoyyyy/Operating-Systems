#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string>
using namespace std;
bool prime(int n)
{
	int c=0;
	for(int i=1;i<=n;i++)
	{
		if(n%i==0)
			c++;
	}
	if(c==2)
		return true;
	else
		return false;
}
int main(int argc,char* argv[]) 
{
  int i; //iterator
  int n; //range
  pid_t p=fork();
  if(p==0){
  char *args[2]={argv[1],NULL}; 
  execv("./fib",args);}
  else{
  wait(NULL);
  n=stoi(argv[1]);
  printf("Prime series\n");
  for(int i=0;i<=n;i++)
  {
  	if(prime(i))
  		printf("%d\n",i);
  }}
  return 0;
}

