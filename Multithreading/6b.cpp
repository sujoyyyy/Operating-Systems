#include <iostream> 
#include <pthread.h> 
#include <time.h> 
#define THREAD_MAX 4 
using namespace std; 
int a[100];int MAX; 
int part = 0; 

void merge(int low, int mid, int high) 
{ 
   int* left = new int[mid - low + 1]; 
   int* right = new int[high - mid]; 
   int n1 = mid - low + 1, n2 = high - mid, i, j;
   for (i = 0; i < n1; i++) 
      left[i] = a[i + low]; 
   for (i = 0; i < n2; i++) 
      right[i] = a[i + mid + 1]; 

   int k = low; 
   i = j = 0; 

   // merge left and right in ascending order 
   while (i < n1 && j < n2) { 
      if (left[i] <= right[j]) 
         a[k++] = left[i++]; 
      else
         a[k++] = right[j++]; 
   } 

   // insert remaining values from left 
   while (i < n1) { 
      a[k++] = left[i++]; 
   } 

   // insert remaining values from right 
   while (j < n2) { 
      a[k++] = right[j++]; 
   } 
} 

void merge_sort(int low, int high) 
{ 
   int mid = low + (high - low) / 2; 
   if (low < high) { 
      merge_sort(low, mid);
      merge_sort(mid + 1, high);  
      merge(low, mid, high); 
   } 
} 

void *merge_sort(void* arg) 
{ 
  
   int thread_part = part++; 

   int low = thread_part * (MAX / 4); 
   int high = (thread_part + 1) * (MAX / 4) - 1; 
   int mid = low + (high - low) / 2; 
   if (low < high) { 
      merge_sort(low, mid); 
      merge_sort(mid + 1, high); 
      merge(low, mid, high); 
   }
   pthread_exit(0); 
} 

int main(int argc, char const *argv[])
{ 
   MAX= argc;
   for (int i = 0; i < argc-1; i++) 
      a[i] = atoi(argv[i+1]);
   pthread_t threads[THREAD_MAX]; 

   // creating 4 threads 
   for (int i = 0; i < 4; i++) 
      pthread_create(&threads[i], NULL, merge_sort,(void*)NULL); 
   for (int i = 0; i < 4; i++) 
      pthread_join(threads[i], NULL); 
   merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1); 
   merge(MAX / 2, MAX/2 + (MAX-1-MAX/2)/2, MAX - 1); 
   merge(0, (MAX - 1)/2, MAX - 1); 

  // displaying sorted array 
   cout << "Sorted array: "; 
   for (int i = 1; i < MAX; i++) 
      cout << a[i] << " ";
   
   cout<<endl;
   return 0; 

}
