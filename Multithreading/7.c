#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define NUM_THREADS 8         
#define TOT_COUNT 10000055      
float randNumGen()
{
   int random_value = rand();   
   float unit_random = random_value / (float) RAND_MAX; 
   return unit_random;
}
void *doCalcs(void *threadid)
{
   long longTid;
   longTid = (long)threadid;
   
   int tid = (int)longTid;      
   float *in_count = (float *)malloc(sizeof(float));
   *in_count=0;
   float tot_iterations= TOT_COUNT/NUM_THREADS;
   
   int counter=0;
   for(counter=0;counter<tot_iterations;counter++){
      float x = randNumGen();
      float y = randNumGen();
      
      float result = x*x+y*y;
      result= sqrt(result);
      
      if(result<1){
         *in_count+=1;}
      
   }
   if(tid==0){
      float remainder = TOT_COUNT%NUM_THREADS;
      
      for(counter=0;counter<remainder;counter++){
      float x = randNumGen();
      float y = randNumGen();
      
      float result = sqrt((x*x) + (y*y));
      
      if(result<1){
         *in_count+=1;               }
      
   }
   }   
   pthread_exit((void *)in_count);     
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   void *status;
   float tot_in=0;
     
   for(t=0;t<NUM_THREADS;t++){
     rc = pthread_create(&threads[t], NULL, doCalcs, (void *)t);
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
     }
   for(t=0;t<NUM_THREADS;t++){
           
      pthread_join(threads[t], &status);      
      tot_in+=*(float*)status;                 
     }
     printf("Value for Pi is %f \n",4*(tot_in/TOT_COUNT));
     pthread_exit(NULL);
}