/*
Do not modify this file.
Make all of your changes to main.c instead.
*/

#define _XOPEN_SOURCE 500L

#include "disk.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define ABS(x) ( (x)<(0) ? -(x) : (x) )

struct disk {
	int fd;
	int block_size;
	int nblocks;
	int nreads;
	int nwrites;
	int last_request;
	int threads_inside;
};

struct disk * disk_open( const char *diskname, int nblocks )
{
	struct disk *d;

	d = malloc(sizeof(*d));
	if(!d) return 0;

	d->fd = open(diskname,O_CREAT|O_RDWR,0777);
	if(d->fd<0) {
		free(d);
		return 0;
	}

	d->block_size = BLOCK_SIZE;
	d->nblocks = nblocks;
	d->last_request = 0;
	d->threads_inside = 0;
	d->nreads = 0;
	d->nwrites = 0;
	
	if(ftruncate(d->fd,d->nblocks*d->block_size)<0) {
		close(d->fd);
		free(d);
		return 0;
	}

	return d;
}

void disk_write( struct disk *d, int block, const char *data )
{
	d->threads_inside++;
	
	if(d->threads_inside>1) {
		fprintf(stderr,"disk-read: CRASH: multiple threads in disk at once!\n");
		abort();
	}
	
	if(block<0 || block>=d->nblocks) {
		fprintf(stderr,"disk_write: CRASH: invalid block #%d\n",block);
		abort();
	}

	// delay for 10ms minimum plus 10ms per 100 blocks moved
	usleep(10000 + 100*ABS(d->last_request-block));
	
	int actual = pwrite(d->fd,(char*)data,d->block_size,block*d->block_size);
	if(actual!=d->block_size) {
		fprintf(stderr,"disk_write: CRASH: failed to write block #%d: %s\n",block,strerror(errno));
		abort();
	}

	d->last_request = block;
	d->threads_inside--;
	d->nwrites++;
}

void disk_read( struct disk *d, int block, char *data )
{
	d->threads_inside++;

	if(d->threads_inside>1) {
		fprintf(stderr,"disk-read: CRASH: multiple threads in disk at once!\n");
		abort();
	}
	
	if(block<0 || block>=d->nblocks) {
		fprintf(stderr,"disk_read: CRASH: invalid block #%d\n",block);
		abort();
	}

	// delay for 10ms minimum plus 10ms per 100 blocks moved
	usleep(10000 + 100*ABS(d->last_request-block));
	
	int actual = pread(d->fd,(char*)data,d->block_size,block*d->block_size);
	if(actual!=d->block_size) {
		fprintf(stderr,"disk_read: CRASH: failed to read block #%d: %s\n",block,strerror(errno));
		abort();
	}

	d->last_request = block;
	d->threads_inside--;
	d->nreads++;
}

int disk_nblocks( struct disk *d )
{
	return d->nblocks;
}

int disk_nreads( struct disk *d )
{
	return d->nreads;
}

int disk_nwrites( struct disk *d )
{
	return d->nwrites;
}

void disk_reset_stats( struct disk *d )
{
	d->nreads = d->nwrites = 0;
}

void disk_close( struct disk *d )
{
	close(d->fd);
	free(d);
}
