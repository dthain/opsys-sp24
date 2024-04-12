/*
This is the implementation of the buffer cache module.
You should make all of your changes here.
Feel free to add any structures, types or helper functions that you need.
*/

#include "bcache.h"
#include "disk.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

/*
A structure describing the entire buffer cache.
You may add and modify this structure as needed.
*/

struct bcache {
	struct disk *disk;    // The disk object underlying the cache.
	int memory_blocks;    // The total number of memory blocks in the cache.
	int nreads;           // A running count of read operations.
	int nwrites;          // A running count of write operations.
};

/*
Create and initialize the buffer cache object.
You may modify this function as needed to set things up.
*/

struct bcache * bcache_create( struct disk *d, int memory_blocks )
{
	struct bcache *bc = malloc(sizeof(*bc));

	bc->disk = d;
	bc->nreads = 0;
	bc->nwrites = 0;
	bc->memory_blocks = memory_blocks;
	
	return bc;
}

/*
Read a block through the buffer cache.
This is a dummy implementation that calls disk_read directly.
It will work only for one thread, and it won't be particularly fast.
Instead, it should manipulate the data structure and wait for the scheduler.
*/

void bcache_read( struct bcache *bc, int blocknum, char *data )
{
	/* Just do the read.  Unsafe! */
	disk_read(bc->disk,blocknum,data);

	/* count the number of reads as we go */
	bc->nreads++;
}

/*
Write a block through the buffer cache.
Like bcache_read, this is a dummy implementation.
*/

void bcache_write( struct bcache *bc, int blocknum, const char *data )
{
	/* Just do the write.  Unsafe! */
	disk_write(bc->disk,blocknum,data);

	/* count the number of writes as we go */
	bc->nwrites++;
}

/*
Block until all dirty blocks in the buffer cache have been cleaned.
This needs to be implemented.
*/

void bcache_sync( struct bcache *bc )
{
}

/*
This is the function that will run the I/O scheduler.
This needs to be implemented.
*/

void * bcache_io_scheduler( void *vbc )
{
	return 0;
}

/*
These functions just return basic information about the buffer cache,
and you shouldn't need to change them.
*/

/* Return the number of memory blocks in the buffer cache. */

int bcache_memory_blocks( struct bcache *bc )
{
	return bc->memory_blocks;
}

/* Return the number of blocks in the underlying disk. */

int bcache_disk_blocks( struct bcache *bc )
{
	return disk_nblocks(bc->disk);
}

/* Return the number of reads performed on this buffer cache. */

int bcache_nreads( struct bcache *bc )
{
	return bc->nreads;
}

/* Return the number of writes performed on this buffer cache. */

int bcache_nwrites( struct bcache *bc )
{
	return bc->nwrites;
}

