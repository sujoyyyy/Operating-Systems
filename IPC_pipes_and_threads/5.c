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
		int *nums = (int*)malloc(2*sizeof(int));
		int originalNum=i,remainder,result=0;
		while (originalNum != 0) 
		{
        remainder = originalNum % 10;
        result += remainder * remainder * remainder;
       	originalNum /= 10;
    	}
    	nums[0]=i;
    	nums[1]=result;
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
	if(param[0]==param[1])
	{
		printf("%d\n",param[0]);
	}
	pthread_exit(0);
}