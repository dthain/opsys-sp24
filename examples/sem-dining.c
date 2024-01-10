/* An example of using semaphores for the dining philosophers problem */
/* Warning: This program results in deadlock.  Can you fix it? */


#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NFORKS 5

sem_t forks[NFORKS];

int sleeptime = 10000000; /* microseconds */

void pickup( int id )
{
  int left = id;
  int right = (id + 1) % NFORKS;
	
  printf("thread %d grabbing fork %d\n",id,left);
  sem_wait(&forks[left]);

  printf("thread %d grabbing fork %d\n",id,right);
  sem_wait(&forks[right]);
}

void putdown( int id )
{
  int left = id;
  int right = (id + 1) % NFORKS;
	
  printf("thread %d releasing fork %d\n",id,left);
  sem_post(&forks[left]);

  printf("thread %d releasing fork %d\n",id,right);
  sem_post(&forks[right]);
}

void * philosopher_thread( void * arg )
{
  int *id_pointer = (int*) arg;
  int id = *id_pointer;

  while(1) {
    printf("thread %d sleeping\n",id);
     usleep(rand()%sleeptime);
     printf("thread %d hungry\n",id);
     pickup(id);
     printf("thread %d eating\n",id);
     usleep(rand()%sleeptime);
     putdown(id);
  }
}

int main( int argc, char *argv[] )
{
  pthread_t threadid[NFORKS];
  int id[NFORKS];
  int i;

  srand(time(0));

  for(i=0;i<NFORKS;i++) {
    sem_init(&forks[i],0,1);
  }

  for(i=0;i<NFORKS;i++) {
    id[i] = i;
    pthread_create(&threadid[i],0,philosopher_thread,&id[i]);
  }

  for(i=0;i<NFORKS;i++) {
    void *result;
    pthread_join(threadid[i],&result);
  }

  printf("main: all threads done.\n");

  return 0;
}

