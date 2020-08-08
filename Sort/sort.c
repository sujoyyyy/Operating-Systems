#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int strtoint(char *str)
{
  int i,x;
  for(x=0,i=0;str[i];i++)
  {


  	if(i==0&& str[i]=='-')
  	   i++;

  	if(str[i]>='0'&& str[i]<='9')
  		x=x*10+(str[i]-48);
  	else
  		break;
  }

  if(str[0]=='-')
  	x=-x;

  return(x);
}



int main(int argc, char *argv[])
{   
	

	if(argc<4)
	{
		printf("Wrong input format\n");
		exit(1);
	}

	int n= strtoint(argv[1]);
	int flag= strtoint(argv[2]);
	printf("Size: %d\n",n );
	printf("A/D status: %d\n",flag );

	int a[100];int j=0;

	for(int i=3;j<n;i++)
	{
		a[j]= strtoint(argv[i]);
		j++;
	}
	if(flag==1)
	{
for (int i = 0; i < n; i++)                     //Loop for ascending ordering
	{
		for (int j = 0; j < n; j++)             //Loop for comparing other values
		{
			if (a[j] > a[i])                //Comparing other array elements
			{
				int tmp = a[i];         //Using temporary variable for storing last value
				a[i] = a[j];            //replacing value
				a[j] = tmp;             //storing last value
			}  
		}
	}
	printf("\n\nAscending : ");                     //Printing message
	for (int i = 0; i < n; i++)                     //Loop for printing array data after sorting
	{
		printf(" %d ", a[i]);
	}
}

if(flag==2){
	for (int i = 0; i < n; i++)                     //Loop for descending ordering
	{
		for (int j = 0; j < n; j++)             //Loop for comparing other values
		{
			if (a[j] < a[i])                //Comparing other array elements
			{
				int tmp = a[i];         //Using temporary variable for storing last value
				a[i] = a[j];            //replacing value
				a[j] = tmp;             //storing last value
			}
		}
	}
	printf("\n\nDescending : ");                    //Printing message
	for (int i = 0; i < n; i++)                     //Loop for printing array data after sorting
	{
		printf(" %d ", a[i]);                   //Printing data
	}

}
printf("\n");
	return 0;
}



