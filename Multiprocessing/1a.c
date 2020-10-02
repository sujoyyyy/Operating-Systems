//Zombie Process
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
int main()
{pid_t child_pid = fork();
if (child_pid > 0)
sleep(40);
else 
exit(0);
return 0;}