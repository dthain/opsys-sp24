/* An example of using a monitor for the producer-consumer problem */


#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NBURGERS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int count = 0;
int nthreads = 10;
int sleeptime = 100000; /* microseconds */

void safe_insert()
{
  pthread_mutex_lock(&mutex);
  printf("thread %d wants to insert\n",(int)pthread_self());
  while(count>=NBURGERS) {
    printf("thread %d checking...\n",(int)pthread_self());
    pthread_cond_wait(&cond,&mutex);
  }
  printf("thread %d inserting\n",(int)pthread_self());
  count++;
  printf("thread %d count: %d\n",(int)pthread_self(),count);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}

void safe_remove()
{
  printf("thread %d wants to remove\n",(int)pthread_self());
  pthread_mutex_lock(&mutex);
  while(count==0) {
    printf("thread %d checking...\n",(int)pthread_self());
    pthread_cond_wait(&cond,&mutex);
  }
  printf("thread %d removing\n",(int)pthread_self());
  count--;
  printf("thread %d count: %d\n",(int)pthread_self(),count);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
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

