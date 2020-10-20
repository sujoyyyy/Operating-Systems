#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;
int L[100][100]; char lcs[100];
void *gen(void *param)
{ 
 	char **argv= (char **)param;
 	char *X = argv[1];
	char *Y = argv[2];
	int m=atoi(argv[3]); int n=atoi(argv[4]);
   // Following code is used to print LCS 
   int index = L[m][n]; 
   //char lcs[index+1]; 
   lcs[index] = '\0'; 
   int i = m, j = n; 
   while (i > 0 && j > 0) 
   { 
      if (X[i-1] == Y[j-1]) 
      { 
          lcs[index-1] = X[i-1]; // Put current character in result 
          i--; j--; index--;     // reduce values of i, j and index 
      } 
      else if (L[i-1][j] > L[i][j-1]) 
         i--; 
      else
         j--; 
   } 
  
	pthread_exit(0);
}
int main(int argc, char  *argv[])
{
    memset(L,-1,sizeof(L));
    pthread_t tid;
	pthread_attr_t attr;
	int m= atoi(argv[argc-2]);
	int n= atoi(argv[argc-1]);
	char *X = argv[1];
	char *Y = argv[2];
	for (int i=0; i<=m; i++) 
  	{ 
     for (int j=0; j<=n; j++) 
     { 
       if (i == 0 || j == 0) 
         L[i][j] = 0; 
       else if (X[i-1] == Y[j-1]) 
         L[i][j] = L[i-1][j-1] + 1; 
       else
         L[i][j] = max(L[i-1][j], L[i][j-1]); 
     } 
    } 
    pthread_attr_init(&attr);
	pthread_create(&tid,NULL,gen,(void *)argv);
	pthread_join(tid,NULL);
	cout << "LCS of " << X << " and " << Y << " is " << lcs<<endl; 
    return 0;
}