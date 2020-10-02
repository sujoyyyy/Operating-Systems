//Orphan Process
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
int pid = fork();
if (pid > 0)
printf("Parent\n");
else if (pid == 0)
{
sleep(30);
printf("Child Process");
}
return 0;
}
