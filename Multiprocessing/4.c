#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#define maxcmd 10

char *argp[100];
int arglen;
char buf[100][100];
int buflen;

char PrevCmd[maxcmd][500];
int cmdno;

void GetArgs(char c[])
{
	int i=0;
	
	arglen = 0;
	
	buflen = 0;

	int eol = 0;
	
	while(eol == 0)
	{
		if(c[i] == '\0')
		{
			eol = 1;
			
			buf[arglen][buflen] = '\0';
				
			argp[arglen] = buf[arglen];
			arglen++;
			
			buflen = 0;
		}
		
		else 
		{
			if(c[i] == ' ')
			{
				buf[arglen][buflen] = '\0';
				
				argp[arglen] = buf[arglen];
				arglen++;

				buflen = 0;
			}
			
			else 
			{
				buf[arglen][buflen] = c[i];
				buflen++;
			}
		}
		
		i++;
	}
	
	argp[arglen] = NULL;
}

void DisplayHistory(int h)
{
	printf("\n");
	
	for(int i=0;i<h && i<maxcmd && cmdno > i;i++)
	{
		int j = (cmdno-1-i)%maxcmd;
		printf("%s\n", PrevCmd[j]);
	}
	
	printf("\n");
}

int main()
{
	char cmd[500];
	
	cmdno = 0;

	while(1)
	{
		printf("@ ");
		scanf(" %[^\n]", cmd);

		if(strcmp(cmd, "exit") == 0)
		{
			return 0;
		}
		
		else if(cmd[0] == '!')
		{
			int h;
			if (!cmd[2])
				h = (int)cmd[1] - 48;
			else
			{
				int x = (int)cmd[1] - 48;
				int y = (int)cmd[2] - 48;
				h = 10*x + y;
			}
			
			DisplayHistory(h);
		}
		
		else 
		{	
			int pid = vfork();
			
			if(pid == 0)
			{
				strcpy(PrevCmd[cmdno%maxcmd], cmd);
				cmdno++;
			
				GetArgs(cmd);
				
				if(execvp(argp[0], argp) == -1)
				{
					printf("%s: command not found.\n", argp[0]);
				}
				exit(0);
			}
			
			else 
			{
				wait(NULL);
				printf("\n");
			}
		}
	}
}
