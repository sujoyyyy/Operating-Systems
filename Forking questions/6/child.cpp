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

	for(int i=1;j<n;i++)
	{
		a[j]= stoi(argv[i]);
		j++;
	}
	
	for (int i = 0; i < n/2; i++)                     //Loop for Ascending ordering
	{
		for (int j = 0; j < n/2; j++)             //Loop for comparing other values
		{
			if (a[j] > a[i])                //Comparing other array elements
			{
				int tmp = a[i];         //Using temporary variable for storing last value
				a[i] = a[j];            //replacing value
				a[j] = tmp;             //storing last value
			}
		}
	}
	printf("Ascending :\n ");                    //Printing message
	for (int i = 0; i < n/2; i++)                     //Loop for printing array data after sorting
	{
		printf(" %d ", a[i]);                   //Printing data
	}

    printf("\n");
	return 0;
}



