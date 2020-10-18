#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
void *gen(void *nums);
int main(int argc, char const *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;
	if (argc<2)
	{
		printf("Wrong Usage\n");
		return 0;
	}
	int n= argc-1;
	int *nums = (int*)malloc((n+1)*sizeof(int));
	for(int i=1;i<argc;i++)
	{	
		nums[i]=atoi(argv[i]);
		
	}
	nums[0]=n;
	pthread_attr_init(&attr);
	pthread_create(&tid,NULL,gen,(void *)nums);
	pthread_join(tid,NULL);
	n=n+1;
	printf("Ascending\n");
	for(int i=1;i<n;i++)
	{
		for (int j = i+1; j < n; ++j )
		{
			if(nums[j]<nums[i])
			{
				int t=nums[i];
				nums[i]=nums[j];
				nums[j]=t;
			}
		}
	}
	for(int i=1;i<n;i++)
	{
		printf("%d   ",nums[i]);
	}
	printf("\n");
	free(nums);
	return 0;
}
void *gen(void *nums)
{
	int *param=(int *)nums;
	int n=param[0];n=n+1;
	printf("Descending\n");
	for(int i=1;i<n;i++)
	{
		for (int j = i+1; j < n; ++j )
		{
			if(param[i]<param[j])
			{
				int t=param[i];
				param[i]=param[j];
				param[j]=t;
			}
		}
	}
	for(int i=1;i<n;i++)
	{
		printf("%d   ",param[i]);
	}
	printf("\n");
	pthread_exit(0);
}