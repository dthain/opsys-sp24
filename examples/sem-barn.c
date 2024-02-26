/*
An example of using semaphores for the barnyard problem.

The barnyard problem: Three barns sit adjacent to a farmyard:
one has cows, one has sheep, the other has wolves.  The yard
can contain up to ten animals at once, however, the wolves
cannot share the yard with the cows or the sheep.

Each animal is represented by a thread (below) running
sheep_thread, cow_thread, and wolf_thread, respectively.
Use semaphores to write functions sheep_enter/leave,
cow_enter/leave, and wolf_enter/leave that control access
to the barnyard.

Frankly, doing this with semaphores is pretty tricky to get
right.  Compare this code with monitor-barn.c to see how
a monitor makes it easier to get it right.
*/


#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

sem_t mutex;     /* Controls access to global variables. */
sem_t empty;     /* Number of empty spaces in barnyard. */
sem_t full;      /* Number of full spaces in barnyard. */
sem_t wolfgate;  /* Set to zero to block entry of wolves. */
sem_t wolfmutex; /* Separate mutex to control wolf access to globals. */

int nsheep = 0;  /* Number of sheep currently in the yard. */
int ncows = 0;   /* Number of cows currently in the yard. */
int nwolves = 0; /* Number of wolves currently in the yard. */

int nthreads = 100;   /* Total number of threads. */
int sleeptime = 1000; /* Maxmimum delay time of each thread. */

void wolf_enter()
{
  printf("wolf wants to enter...\n");
  /* Wait for the wolfgate to be open, and claim it. */
  sem_wait(&wolfgate);

  /* Protect access to global variables with the wolfmutex. */
  sem_wait(&wolfmutex);
  nwolves++;
  printf("%d sheep %d cows %d wolves in the barnyard!\n",nsheep,ncows,nwolves);
  sem_post(&wolfmutex);
}

void wolf_leave()
{
  printf("wolf leaving\n");

  /* Protect access to global variables with the wolfmutex. */
  sem_wait(&wolfmutex);
  nwolves--;
  printf("%d sheep %d cows %d wolves in the barnyard!\n",nsheep,ncows,nwolves);
  sem_post(&wolfmutex);

  /* Put the wolfgate back to open */
  sem_post(&wolfgate);
}

void sheep_enter()
{
  printf("sheep wants to enter...\n");
  /* Wait for one of ten spots to become available. */
  sem_wait(&empty);
  sem_post(&full);

  /* If we are the first sheep or cow to enter, close the wolfgate. */
  /* Protect access to global variables with the mutex. */
  sem_wait(&mutex);
  if(nsheep==0 && ncows==0) sem_wait(&wolfgate);
  nsheep++;
  printf("%d sheep %d cows %d wolves in the barnyard!\n",nsheep,ncows,nwolves);
  sem_post(&mutex);
}

void sheep_leave()
{
  printf("sheep leaving\n");

  /* If we are the last sheep or cow to exit, open the wolfgate. */
  sem_wait(&mutex);
  nsheep--;
  if(nsheep==0 && ncows==0) sem_post(&wolfgate);
  printf("%d sheep %d cows %d wolves in the barnyard!\n",nsheep,ncows,nwolves);
  sem_post(&mutex);

  /* Release one of the ten spots. */
  sem_wait(&full);
  sem_post(&empty);
}

void cow_enter()
{
  printf("cow wants to enter...\n");
  /* Wait for one of ten spots to become available. */
  sem_wait(&empty);
  sem_post(&full);

  /* If we are the first sheep or cow to enter, close the wolfgate. */
  /* Protect access to global variables with the mutex. */
  sem_wait(&mutex);
  if(nsheep==0 && ncows==0) sem_wait(&wolfgate);
  ncows++;
  printf("%d sheep %d cows %d wolves in the barnyard!\n",nsheep,ncows,nwolves);
  sem_post(&mutex);
}

void cow_leave()
{
  printf("cow leaving\n");

  /* If we are the last sheep or cow to exit, open the wolfgate. */
  sem_wait(&mutex);
  ncows--;
  if(nsheep==0 && ncows==0) sem_post(&wolfgate);
  printf("%d sheep %d cows %d wolves in the barnyard!\n",nsheep,ncows,nwolves);
  sem_post(&mutex);

  /* Release one of the ten spots. */
  sem_wait(&full);
  sem_post(&empty);
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

  sem_init(&mutex,0,1);
  sem_init(&empty,0,10);
  sem_init(&full,0,0);
  sem_init(&wolfgate,0,1);
  sem_init(&wolfmutex,0,1);
  
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

