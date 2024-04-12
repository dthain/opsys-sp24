/*
The main program of the buffer cache assignment.
You should read and understand this file, but shouldn't change it.
*/

#include "program.h"
#include "bcache.h"
#include "disk.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

int main( int argc, char *argv[] )
{
	if(argc!=4) {
		printf("use: %s <nthreads> <buffer-blocks> <disk-blocks>\n",argv[0]);
		return 1;
	}

	int nthreads = atoi(argv[1]);
	int bblocks = atoi(argv[2]);
	int dblocks = atoi(argv[3]);
	int i;
	
	printf("Creating disk image %s with %d disk blocks\n","myvirtualdisk",dblocks);
	struct disk *thedisk = disk_open("myvirtualdisk",dblocks);
	if(!thedisk) {
		printf("couldn't open %s: %s\n","myvirtualdisk",strerror(errno));
		return 1;
	}

	printf("Writing known values to the disk...\n");
	program_fill_disk(thedisk);
	disk_reset_stats(thedisk);
		
	printf("Creating buffer/cache with %d memory blocks\n",bblocks);
	struct bcache *thecache = bcache_create(thedisk,bblocks);
	
	printf("Starting I/O scheduler thread\n");
	pthread_t scheduler_tid;
	pthread_create(&scheduler_tid,0,bcache_io_scheduler,thecache);

	struct timeval starttime;
	struct timeval stoptime;
	
	gettimeofday(&starttime,0);

	printf("Starting %d program threads...\n",nthreads);
	pthread_t *program_tid = malloc(sizeof(pthread_t)*nthreads);
	for(i=0;i<nthreads;i++) {
		pthread_create(&program_tid[i],0,program_thread,thecache);
	}

	printf("Waiting for programs to complete...\n");
	for(i=0;i<nthreads;i++) {
		pthread_join(program_tid[i],0);
	}

	printf("Syncing buffer cache...\n");
	bcache_sync(thecache);
		      
	gettimeofday(&stoptime,0);

	double elapsed = stoptime.tv_sec - starttime.tv_sec + stoptime.tv_usec/1000000.0 - starttime.tv_usec/1000000.0;

	int disk_ops = disk_nreads(thedisk)+disk_nwrites(thedisk);
	int bcache_ops = bcache_nreads(thecache)+bcache_nwrites(thecache);

	printf("System Performance:\n");
	printf("-------------------\n");
	printf(" elapsed time: %.2lfs\n",elapsed);
	printf("bcache  reads: %d\n",bcache_nreads(thecache));
	printf("bcache writes: %d\n",bcache_nwrites(thecache));
	printf("bcache   perf: %.2lf ops/s\n",(double)bcache_ops/elapsed);
	printf("  disk  reads: %d\n",disk_nreads(thedisk));
	printf("  disk writes: %d\n",disk_nwrites(thedisk));
	printf("  disk   perf: %.2lf ops/s\n",(double)disk_ops/elapsed);
	
	disk_close(thedisk);

	return 0;
}
