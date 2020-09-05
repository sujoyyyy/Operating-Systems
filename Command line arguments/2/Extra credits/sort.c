#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int max( int[],int);
int min( int[],int);
void sort(int (*)(int[],int),int[],int);
void print_array(int[],int);
int strtoint(char *str)
{
  int x;
  x= atoi(str);

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

	if(flag>2){
		printf("Wrong input format\n");
		exit(1);
	}



	int a[100];int j=0;int b[100],k=0;

	for(int i=3;j<n;i++)
	{
		a[j]= strtoint(argv[i]);
		j++;
	}
	for (k=0;k<n;k++)
	   b[k]=a[k];

	
    

    if (flag==2){
      sort(max,a,n);
      printf("\n\n The array in descending order\n\n");
      print_array(a,n);}
    else{
      sort(min,b,n);
      printf("\n\n The array in ascending order\n\n");
      print_array(b,n);}

	return 0;
}

void sort(int (*first)(int[],int),int array[], int count )
  {
    int k,index,back_count,temp;
    back_count=count;

    for (k=0 ; k < count-1 ; k++)
     {
      index=(*first)(&array[k],back_count)+k;
      if (index != k )
       {
        temp=array[k];
	array[k]=array[index];
	array[index]=temp;
       }
       back_count--;
      }
    }

 void print_array(int array[], int count)
    {
     int j;

     for (j=0;j <= count-1 ; j++)
      { 
       printf("%d    ",

       	array[j]);
      }
     
     }
int max( int exam[], int n ){
	int xmax,index,j;
	  xmax=exam[0];
	  index=0;
	for (j=1;j <= n-1 ; j++)
	  {
	   if (exam[j] > xmax )
	    {
	     xmax=exam[j];
	     index=j;
        }
      }
          return(index);
}                                                  

int min( int exam[], int n ){
int xmin,index,j;
	  xmin=exam[0];
	  index=0;
	  for (j=1;j <= n-1 ; j++)
	   {
	   if (exam[j] < xmin )
	    {
	     xmin=exam[j];
	     index=j;
            }
           }
          return(index);
         }                                                  


