#ifndef BCACHE_H
#define BCACHE_H

/*
The interface to the buffer cache module.
You should read and understand this file, but shouldn't change it.
*/

#include "disk.h"

/* Create a new buffer cache layer with a given disk d and memory blocks. */
struct bcache * bcache_create( struct disk *d, int memoryblocks );

/* Read a block out of the buffer cache, and fill "buffer" with 4KB of data. */
void bcache_read( struct bcache *bc, int block, char *buffer );

/* Write a block in the buffer cache, filling in with 4KB of provided data. */
void bcache_write( struct bcache *bc, int block, const char *data );

/* Block until all dirty blocks in the buffer cache have been written. */
void bcache_sync( struct bcache *bc );

/* The function containing the background I/O scheduler. */
void * bcache_io_scheduler( void *bc );

/* Return the number of memory blocks in the buffer cache. */
int bcache_memory_blocks( struct bcache *bc );

/* Return the number of blocks in the disk underlying the cache. */
int bcache_disk_blocks( struct bcache *bc );

/* Return the total number of reads performed on this cache. */
int bcache_nreads( struct bcache *bc );

/* Return the total number of writes performed on this cache. */
int bcache_nwrites( struct bcache *bc );

#endif
