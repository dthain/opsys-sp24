/* Example of using monitors to solve the bank account problem. */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;
int balance = 200;
int nthreads = 10;

int sleeptime = 1000000;

void deposit( int amount )
{
  pthread_mutex_lock(&mutex);
  balance += amount;
  printf("thread %d deposit %d balance %d\n",(int)pthread_self(),amount,balance);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}

void withdraw( int amount )
{
  pthread_mutex_lock(&mutex);
  while(balance<amount) {
    printf("thread %d withdraw %d waiting\n",(int)pthread_self(),amount);
    pthread_cond_wait(&cond,&mutex);
  }
  balance-=amount;
  printf("thread %d withdraw %d balance %d\n",(int)pthread_self(),amount,balance);
  pthread_mutex_unlock(&mutex);
}

void * user_thread( void * arg )
{
  while(1) {
    if(rand()%2) {
      deposit( rand()%100 );
    } else {
      withdraw( rand()%100 );
    }
    usleep(rand()%sleeptime);
  }

}

int main( int argc, char *argv[] )
{
  pthread_t tid[nthreads];
  int i;

  srand(time(0));

  for(i=0;i<nthreads;i++) {
    pthread_create(&tid[i],0,user_thread,0);
  }

  for(i=0;i<nthreads;i++) {
    void *result;
    pthread_join(tid[i],&result);
  }

  printf("main: all threads done.\n");

  return 0;
}

