#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;
void *gen(void *nums);

int main(int argc, char const *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	if (argc<2)
	{
		printf("Wrong Usage, correct : ./<executable><key><array elements>\n");
		return 0;
	}
	int n= argc-2;
  int key=atoi(argv[1]);
	int *nums = (int*)malloc((argc)*sizeof(int));
	for(int i=2;i<argc;i++)
	{	
		nums[i]=atoi(argv[i]);
		
	}
  nums[0]=n;
  nums[1]=key;
	pthread_attr_init(&attr);
	pthread_create(&tid,NULL,gen,(void *)nums);
	pthread_join(tid,NULL);int count=0;
	//parent code
  for (int i = 0;i < n-2; ++i)
  {
    nums[i]=nums[i+2];
  }
	sort(nums,nums+n/2);
	int beg=0;
 	int end=n/2;
  while(beg<=end)
  {
 	 int mid=(beg+end)/2;
 	 if(nums[mid]==key)
  	{
    count++;
    for(int i=mid+1;i<end;i++)
    	if(nums[i]==key)
    		count++;
    	else
    		break;
    for(int i=beg;i<mid;i++)
    	if(nums[i]==key)
    		count++;
    	else
    		break;
    break;
 	}
  	else if(nums[mid]<key)
  	{
    	beg=mid+1;
  	}
 	else
    	end=mid-1;
  }
  printf("Occurences in first half = %d\n",count);
	printf("\n");
	free(nums);
	return 0;
}
void *gen(void *nums)
{
	int *a=(int *)nums; 
  int n= a[0];
  int key=a[1];
  for (int i = 0;i < n-2; ++i)
  {
    a[i]=a[i+2];
  }
  //printf("%d\n",n);
  int count=0;
	//child code
	sort(a+n/2,a+n);
	int beg=n/2;
	int end=n;
	bool flag=false;
	while(beg<=end)
	{
  	int mid=(beg+end)/2;
 		if(a[mid]==key)
  		{
    		count++;
    		for(int i=mid+1;i<end;i++)
      		if(a[i]==key)
        		count++;
      		else
        		break;
    		for(int i=beg;i<mid;i++)
      		if(a[i]==key)
        		count++;
      		else
        		break;
    		break;
  		}
  		else if(a[mid]<key)
  		{
    		beg=mid+1;
  		}
  		else
    		end=mid-1;
	}
 	printf("Occurences in second half = %d\n",count);
	printf("\n");
	pthread_exit(0);
}