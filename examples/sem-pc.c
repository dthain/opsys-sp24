/* An example of using semaphores for the producer-consumer problem */


#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NBURGERS 4

sem_t mutex;
sem_t full;
sem_t empty;

int count = 0;
int nthreads = 3;
int sleeptime = 1000; /* microseconds */

void safe_insert()
{
  printf("thread %d wants to insert\n",(int)pthread_self());
  sem_wait(&empty);
  printf("thread %d inserting\n",(int)pthread_self());
  sem_wait(&mutex);
  count++;
  printf("thread %d count: %d\n",(int)pthread_self(),count);
  sem_post(&mutex);
  sem_post(&full);
}

void safe_remove()
{
  printf("thread %d wants to remove\n",(int)pthread_self());
  sem_wait(&full);
  printf("thread %d removing\n",(int)pthread_self());
  sem_wait(&mutex);
  count--;
  printf("thread %d count: %d\n",(int)pthread_self(),count);
  sem_post(&mutex);
  sem_post(&empty);
}

void * producer_thread( void * arg )
{
  while(1) {
    usleep(rand()%sleeptime);
    safe_insert();
  }
}

void * consumer_thread( void * arg )
{
  while(1) {
    usleep(rand()%sleeptime);
    safe_remove();
  }
}

int main( int argc, char *argv[] )
{
  pthread_t producer_tid[nthreads];
  pthread_t consumer_tid[nthreads];
  int i;

  srand(time(0));

  sem_init(&mutex,0,1);
  sem_init(&full,0,0);
  sem_init(&empty,0,NBURGERS);

  for(i=0;i<nthreads;i++) {
    pthread_create(&producer_tid[i],0,producer_thread,0);
  }

  for(i=0;i<nthreads;i++) {
    pthread_create(&consumer_tid[i],0,consumer_thread,0);
  }

  for(i=0;i<nthreads;i++) {
    void *result;
    pthread_join(producer_tid[i],&result);
    pthread_join(consumer_tid[i],&result);
  }

  printf("main: all threads done.\n");

  return 0;
}

