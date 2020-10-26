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
	int n= atoi(argv[1]);
	for(int i=1;i<=n;i++)
	{	
		int *nums = (int*)malloc(sizeof(int));
    	nums[0]=i;
		pthread_attr_init(&attr);
		pthread_create(&tid,NULL,gen,(void *)nums);
		pthread_join(tid,NULL);
		free(nums);

	}
	return 0;
}
void *gen(void *nums)
{
	int *param=(int *)nums;
	int x= param[0];int c=0;
	for(int i=1;i<=x;i++)
	{
		if(x%i==0)
			c++;
	}
	if(c==2)
		printf("%d\n",x);
	pthread_exit(0);
}