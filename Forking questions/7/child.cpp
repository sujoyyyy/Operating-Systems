#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string>
using namespace std;
int main(int argc, char *argv[])
{   
	

	int n= stoi(argv[0]);
	int a[100];int j=0;
	int key=stoi(argv[1]);

	for(int i=2;j<n;i++)
	{
		a[j]= stoi(argv[i]);
		j++;
	}
	
int beg=n/2;
int end=n;
bool flag=false;
while(beg<=end)
{
  int mid=(beg+end)/2;
  if(a[mid]==key)
  {
    flag=true;
    break;
  }
  else if(a[mid]<key)
  {
    beg=mid+1;
  }
  else
    end=mid-1;
}
if(flag==false)
{
  printf("Not found in second half\n");
}
else
{
  printf("Found in second half\n");
}
}



