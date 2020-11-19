#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#define BufferSize 5 // Size of the buffer

int in = 0;
int out = 0;
int buffer[BufferSize];

void *producer(void *pno)
{   
        int item;
        item = rand()%101; // Produce an random item
        buffer[in] = item;
        printf("Producer Insert Item %d at %d\n",buffer[in],in);
        in = (in+1)%BufferSize;
        
}

void *consumer(void *cno)
{   
       
        int item = buffer[out];
        printf("Consumer Remove Item %d from %d\n",item, out);
        out = (out+1)%BufferSize;
        
   
}

int main()
{   
    srand(time(0));
    pthread_t pro[5],con[5];
    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, NULL);
        pthread_create(&con[i], NULL, (void *)consumer, NULL);
        
    }
    
    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
        pthread_join(con[i], NULL);
    }
    return 0;
}