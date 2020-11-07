#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
int arrradix[10000];
int array[10000];
struct data
{
	int arr[10000];
	int n;
};

struct count_sort_data
{
	struct data *d;
	int exp;
};

int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}
void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);

	printf("\n");
}

void *countSort(void *param)
{
	
	struct count_sort_data *csd = (struct count_sort_data *)param;

	int output[(csd->d)->n]; // output array
	int i, count[10] = {0};

	for (i = 0; i < (csd->d)->n; i++)
		count[((csd->d)->arr[i] / csd->exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (i = (csd->d)->n - 1; i >= 0; i--)
	{
		output[count[((csd->d)->arr[i] / csd->exp) % 10] - 1] = (csd->d)->arr[i];
		count[((csd->d)->arr[i] / csd->exp) % 10]--;
		//print(output, (csd->d)->n);
	}

	for (i = 0; i < (csd->d)->n; i++)
		(csd->d)->arr[i] = output[i];

	//print((csd->d)->arr, (csd->d)->n);
	pthread_exit(0);
}

void *RadixSort(void *param)
{
	
	struct data *d = param;
	int m = getMax(d->arr, d->n);

	printf("Enter number of threads: \n");
	int noofthreads = 0;
	scanf("%d",&noofthreads);
	struct count_sort_data cd[noofthreads];
	pthread_t tid[noofthreads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//printf("Passes for Radix Sort\n");
	int i = 0;
	for (int exp = 1; m / exp > 0; exp *= 10)
	{

		cd[i].d = d;
		cd[i].exp = exp;
		pthread_create(&tid[i], &attr, countSort, &cd[i]);
		i++;
		
	}
	for (int j = 0; j < i; ++j)
	{
		pthread_join(tid[j], NULL);
		j++;
	}
	pthread_exit(0);
}

void *BubbleSort(void *param)
{
	struct data *d = param;
	//printf("\nPasses for BubbleSort: \n");
	for (int i = 1; i < d->n; i++)
	{
		int tcheck = 0;
		for (int j = 0; j < d->n - i; j++)
		{
			if (d->arr[j] > d->arr[j + 1])
			{
				int temp = d->arr[j];
				d->arr[j] = d->arr[j + 1];
				d->arr[j + 1] = temp;
				tcheck = 1;
			}
		}
		//print(d->arr, d->n);
		if (tcheck == 0)
			break;
	}

	pthread_exit(0);
}

void *InsertionSort(void *param)
{
	struct data *d = param;
	//printf("\nPasses for Insertion Sort: \n");
	for (int i = 1; i < d->n; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (d->arr[j - 1] > d->arr[j])
			{
				int temp = d->arr[j];
				d->arr[j] = d->arr[j - 1];
				d->arr[j - 1] = temp;
			}
			else
				break;
		}
		//print(d->arr, d->n);
	}

	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	clock_t t1, t2;
	srand(time(0));
	if (argc < 2)
		printf("Wrong number of parameters.\n");
	else
	{
		int n = atoi(argv[1]);
		printf("The array of size %d will be filled with random numbers.\n",n);
		for (int i = 0; i < n; i++)
		{
			arrradix[i] = rand()%101;
			array[i] = rand()%101;
		}

		struct data d[3];
		for (int i = 0; i < n; i++)
		{
			d[0].arr[i] = arrradix[i];
			d[1].arr[i] = arrradix[i];
			d[2].arr[i] = arrradix[i];
		}
		d[0].n = n;
		d[1].n = n;
		d[2].n = n;

		pthread_t tid[3];
		pthread_attr_t attr;
		pthread_attr_init(&attr);


		t1 = clock();
		pthread_create(&tid[0], &attr, RadixSort, &d[0]);
		pthread_join(tid[0], NULL);
		t2 = clock();

		printf("\nRadix Sorted: ");
	//	for (int i = 0; i < n; i++)
		//	printf("%d ", d[0].arr[i]);

		printf("\nRun time: %f\n\n", (t2 - t1) / (double)CLOCKS_PER_SEC);

		t1 = clock();
		pthread_create(&tid[1], &attr, BubbleSort, &d[1]);
		pthread_join(tid[1], NULL);
		t2 = clock();

		printf("\nBubble Sorted: ");
		//for (int i = 0; i < n; i++)
	//			printf("%d ", d[1].arr[i]);

		printf("\nRun time: %f\n\n", (t2 - t1) / (double)CLOCKS_PER_SEC);

		t1 = clock();
		pthread_create(&tid[2], &attr, InsertionSort, &d[2]);
		pthread_join(tid[2], NULL);
		t2 = clock();

		printf("\nInsertion Sorted: ");
		//for (int i = 0; i < n; i++)
		//	printf("%d ", d[2].arr[i]);

		printf("\nRun time: %f\n\n", (t2 - t1) / (double)CLOCKS_PER_SEC);
	}
}