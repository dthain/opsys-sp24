/* An example of using semaphores for the readers-writers problem */


#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

sem_t mutex;
sem_t writelock;
int   readcount=0;
int   value = 0;

int nthreads = 100;
int sleeptime = 10000; /* microseconds */

int safe_read()
{
  sem_wait(&mutex);
  readcount++;
  if(readcount==1) sem_wait(&writelock);
  sem_post(&mutex);

  int result = value;

  sem_wait(&mutex);
  readcount--;
  if(readcount==0) sem_post(&writelock);
  sem_post(&mutex);

  return result;
}

void safe_write( int newvalue )
{
  sem_wait(&writelock);
  value = newvalue;
  sem_post(&writelock);
}

void * reader_writer_thread( void * arg )
{
  while(1) {
    usleep(rand()%sleeptime);
    if(rand()%2) {
      printf("thread %d reading value...\n",(int)pthread_self());
      int v = safe_read();
      printf("thread %d read value %d\n",(int)pthread_self(),v);
    } else {
      int v = rand()%100;
      printf("thread %d writing value %d\n",(int)pthread_self(),v);
      safe_write(v);
      printf("threed %d done writing %d\n",(int)pthread_self(),v);
    }
  }
}

int main( int argc, char *argv[] )
{
  pthread_t tid[nthreads];
  int i;

  srand(time(0));

  sem_init(&mutex,0,1);
  sem_init(&writelock,0,1);
  readcount = 0;
  value = 0;

  for(i=0;i<nthreads;i++) {
    pthread_create(&tid[i],0,reader_writer_thread,0);
  }

  for(i=0;i<nthreads;i++) {
    void *result;
    pthread_join(tid[i],&result);
  }

  printf("main: all threads done.\n");

  return 0;
}

