#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

typedef struct qsort_starter
{
  int *arr;
  int low;
  int high;
  int depthOfThreadCreation;
} quickSort_parameters;

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}


int partition (int *arr, int low, int high, int pivot)
{
	int pivotValue = arr[pivot];
  swap(&arr[pivot],&arr[high]); 
	int s = low; 

	for (int i = low; i <high; i++)
	{
		if (arr[i] <= pivotValue)
		{
			swap(&arr[i], &arr[s]);
      s++; 
		}
	}
	swap(&arr[s], &arr[high]);
	return s;
}
void quickSort(int *arr, int low, int high)
{
	if (low < high)
	{
    int pivotPosition = low+ (high-low)/2;
    pivotPosition= partition(arr, low, high, pivotPosition);
		quickSort(arr, low, pivotPosition - 1);
		quickSort(arr, pivotPosition + 1, high);
	}
}
void concurrent_quickSort(int *arr, int low, int high, int depthOfThreadCreation);
void* worker_quickSort(void * initialValues){
  quickSort_parameters* parameters = initialValues;
  concurrent_quickSort(parameters->arr, parameters->low, parameters->high,parameters->depthOfThreadCreation);
  return NULL;
}
void concurrent_quickSort(int *arr, int low, int high, int depthOfThreadCreation){
    if (low < high){

          int pivotPos = low + (high - low)/2;
          pivotPos = partition(arr, low, high, pivotPos);
          pthread_t thread;


        if (depthOfThreadCreation > 0){
            quickSort_parameters thread_param = {arr, low, pivotPos-1, depthOfThreadCreation};
            int result;
            result = pthread_create(&thread, NULL, worker_quickSort, &thread_param);
            concurrent_quickSort(arr, pivotPos+1, high, depthOfThreadCreation);
            pthread_join(thread, NULL);

        } else
        {
            quickSort(arr, low, pivotPos-1);
            quickSort(arr, pivotPos+1, high);
         }
    }
}
int main(int argc, char **argv)
{
    int depthOfThreadCreation = 4;
    int *arrayElements = malloc((argc-1)*sizeof(int));
    int size=argc-1;
    for (int i=0 ; i<size ; i++){
        arrayElements[i] = atoi(argv[i+1]);
    }

    printf("Unsorted\n");
    for(int i=0; i<size; i++){
      printf("%d ", arrayElements[i]);
    }
    concurrent_quickSort(arrayElements, 0, size-1, depthOfThreadCreation);
    printf("\n");
    printf("Sorted\n");

    for(int i=0; i<size; i++)
    {
      printf("%d ", arrayElements[i]);
    }
    printf("\n");
    free(arrayElements);
    return 0;
}