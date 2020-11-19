#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <stdio.h>
sem_t wrt; char search[100];
pthread_mutex_t mutex;
int numreader = 0;int k=0;
typedef struct 
{
	char word[100];
	char primary[1000];
	char secondary[100];
} dict;
dict dictionary[5];
void *writer(void *wno)
{   
    sem_wait(&wrt);
    printf("Enter word:\n");
    scanf("%s",dictionary[k].word);
    printf("Enter meaning:\n");
    scanf("%s",dictionary[k].primary);
    printf("Enter secondary meaning:\n");
    scanf("%s",dictionary[k].secondary);
    printf("Writer added a word %s.\n",dictionary[k].word);k++;
    sem_post(&wrt);
}
void *reader(void *rno)
{   
    // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); // If this id the first reader, then it will block the writer
    }
    pthread_mutex_unlock(&mutex);
    // Reading Section
    int i;
    printf("Enter word you wanna search: \n");
    scanf("%s",search);
    for(i=0;i<5;i++)
    {
    	if(strcmp(dictionary[i].word,search)==0)
    	{
    		printf("Meaning: %s\n",dictionary[i].primary);
    		printf("Secondary Meaning: %s\n",dictionary[i].secondary);
    	}
    }
    if(i==6)
    {
    	printf("Not Found\n");
    }
     // Reader acquire the lock before modifying numreader
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{   

    pthread_t read[5],write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);
    for(int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, (void *)writer, NULL);
    }

    for(int i = 0; i < 5; i++) {
        pthread_create(&read[i], NULL, (void *)reader, NULL);
    }
    
    for(int i = 0; i < 5; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}