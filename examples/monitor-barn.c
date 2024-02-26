/*
An example of using a monitor for the barnyard problem.

The barnyard problem: Three barns sit adjacent to a farmyard:
one has cows, one has sheep, the other has wolves.  The yard
can contain up to ten animals at once, however, the wolves
cannot share the yard with the cows or the sheep.

Each animal is represented by a thread (below) running
sheep_thread, cow_thread, and wolf_thread, respectively.
Use monitors to write functions sheep_enter/leave,
cow_enter/leave, and wolf_enter/leave that control access
to the barnyard.

Compare this code to sem-barn.c.  IMHO, it's much easier
to get this right using monitors.
*/


#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;  /* Single mutex to control access to globals. */
pthread_cond_t  cond;   /* Single condition variable to wake everyone up. */

int nsheep = 0;  /* Number of sheep currently in the yard. */
int ncows = 0;   /* Number of cows currently in the yard. */
int nwolves = 0; /* Number of wolves currently in the yard. */

int nthreads = 100;   /* Total number of threads. */
int sleeptime = 1000; /* Maxmimum delay time of each thread. */

void wolf_enter()
{
  pthread_mutex_lock(&mutex);
  printf("wolf wants to enter...\n");
  while(nsheep>0 || ncows>0 || nwolves>10) pthread_cond_wait(&cond,&mutex);
  nwolves++;
  printf("%d sheep %d cows %d wolves in the barnyard!\n",nsheep,ncows,nwolves);
  pthread_mutex_unlock(&mutex);
}

void wolf_leave()
{
  pthread_mutex_lock(&mutex);
  printf("wolf leaving\n");
  nwolves--;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}

void sheep_enter()
{
  pthread_mutex_lock(&mutex);
  printf("sheep wants to enter...\n");
  while(nwolves>0 || (ncows+nsheep)>10 ) pthread_cond_wait(&cond,&mutex);
  nsheep++;
  printf("%d sheep %d cows %d wolves in the barnyard!\n",nsheep,ncows,nwolves);
  pthread_mutex_unlock(&mutex);
}

void sheep_leave()
{
  pthread_mutex_lock(&mutex);
  printf("sheep leaving\n");
  nsheep--;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}

void cow_enter()
{
  pthread_mutex_lock(&mutex);
  printf("cow wants to enter...\n");
  while(nwolves>0 || (ncows+nsheep)>10 ) pthread_cond_wait(&cond,&mutex);
  ncows++;
  printf("%d sheep %d cows %d wolves in the barnyard!\n",nsheep,ncows,nwolves);
  pthread_mutex_unlock(&mutex);
}

void cow_leave()
{
  pthread_mutex_lock(&mutex);
  printf("cow leaving\n");
  ncows--;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}

void * wolf_thread( void * arg )
{
	int i;
	for(i=0;i<100;i++) {
		wolf_enter();
		usleep(rand()%sleeptime);
		wolf_leave();
	}

	return 0;
}

void * sheep_thread( void * arg )
{
	int i;
	for(i=0;i<100;i++) {
		sheep_enter();
		usleep(rand()%sleeptime);
		sheep_leave();
	}

	return 0;
}

void * cow_thread( void * arg )
{
	int i;
	for(i=0;i<100;i++) {
		cow_enter();
		usleep(rand()%sleeptime);
		cow_leave();
	}

	return 0;
}

int main( int argc, char *argv[] )
{
  pthread_t tid[nthreads];
  int i;

  srand(time(0));

  pthread_mutex_init(&mutex,0);
  pthread_cond_init(&cond,0);
  
  for(i=0;i<nthreads;i++) {
 	  pthread_create(&tid[i],0,i%3==0 ? sheep_thread : i%3==1 ? cow_thread : wolf_thread ,0);
  }

  for(i=0;i<nthreads;i++) {
    void *result;
    pthread_join(tid[i],&result);
  }

  printf("main: all threads done.\n");

  return 0;
}

