#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#define RD_END 0
#define WR_END 1
int main(int argc, char const *argv[])
{
	int pipefd1[2],pipefd2[2];
	int status1, status2;
	char str1[3]="abc";
	char str2[3]="def";
	char str4[6];
	status1= pipe(pipefd1);
	if(status1==-1)
	{
		printf("Pipe Failed\n");
		return 0;
	}
	status2= pipe(pipefd2);
	if(status2==-1)
	{
		printf("Pipe Failed\n");
		return 0;
	}
	pid_t pid= fork();
	if(pid==0)
	{
		//child
		close(pipefd1[RD_END]);
		close(pipefd2[WR_END]);
		write(pipefd1[WR_END],str2,sizeof(str2)+1);
		read(pipefd2[RD_END],str4,sizeof(str4));
		printf("The concatenated string sent by the parent is %s\n",str4);
	}
	else
	{
		//parent
		close(pipefd1[WR_END]);
		close(pipefd2[RD_END]);
		read(pipefd1[RD_END],str2,sizeof(str2));int k=0;
		//concat
		for(int i=0;i<3;i++)
		{
			str4[i]=str1[i];
		}
		for(int j=3;j<6;j++)
		{
			str4[j]=str2[k];
			k++;
		}
		write(pipefd2[WR_END],str4,sizeof(str4)+1);
	}
	return 0;
}