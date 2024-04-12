/*
This is the implementation of the simulated programs accessing the disk.
You are welcome to read this file, but don't change it.
*/

#include "bcache.h"
#include "disk.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define ITERATIONS 100

/*
Check that the data block returned is the one expected.
The cache must return the proper data!
*/

static void check_data( const char *data, int expected_block )
{
	int i;
	for(i=0;i<BLOCK_SIZE;i+=16) {
		if(data[i] != (char)expected_block) {
			printf("CRASH: bcache_read of block %d returned incorrect data from block %d instead!\n",expected_block,data[i]);
			abort();
		}
	}
}

/*
Fill up the disk with known values so we can check them later.
*/

void program_fill_disk( struct disk *d )
{
	char data[BLOCK_SIZE];
	int i,j;
	
	for(i=0;i<disk_nblocks(d);i++) {
		for(j=0;j<BLOCK_SIZE;j+=16) {
			data[j] = (char)i;
		}
		disk_write(d,i,data);
	}
}


/*
The alpha program alternates between accessing the first 10%
of the disk randomly, and the other 90% randomly.
*/

void program_alpha( struct bcache *bc )
{
	int disk_blocks = bcache_disk_blocks(bc);
	char data[BLOCK_SIZE];
	
	int i;
	for(i=0;i<ITERATIONS;i++) {
		int blocknum;
		if(i%2) {
			blocknum = rand()%disk_blocks/10;
		} else {
			blocknum = disk_blocks/10 + rand()%(9*disk_blocks/10);
		}
		bcache_read(bc,blocknum,data);
		check_data(data,blocknum);
	}
}

/*
The beta program starts in the middle of the disk and "walks"
ten blocks forward, then goes back 9 blocks and starts over,
for a total of ITERATIONS blocks.
*/

void program_beta( struct bcache *bc )
{
	int i, j;
	int disk_blocks = bcache_disk_blocks(bc);
	char data[BLOCK_SIZE];

	for(i=0;i<10;i++) {
		for(j=0;j<10;j++) {
			int blocknum = (disk_blocks/2+(i+j))%disk_blocks;
			bcache_read(bc,blocknum,data);
			check_data(data,blocknum);
		}
	}
	
}

/*
The gamma program writes the first 1/4 of the disk sequentially, four times.
*/

void program_gamma( struct bcache *bc )
{
	int i, j;
	int disk_blocks = bcache_disk_blocks(bc);
	char data[BLOCK_SIZE];

	for(j=0;j<ITERATIONS;j++) {
		/* choose a random block at a multiple of ten */
		int blocknum = j % (disk_blocks/4);
		
		/* fill the block with a pattern based on the block number */
		for(i=0;i<BLOCK_SIZE;i++ ){
			data[i] = (blocknum + i)%256;
		}

		/* reset every 16th value */
		for(i=0;i<BLOCK_SIZE;i+=16) {
			data[i] = (char)blocknum;
		}

		/* write the block out */
		bcache_write(bc,blocknum,data);
	}
}

/* For each thread started, round-robin between each program type. */

void * program_thread( void *vbc )
{
	struct bcache *bc = vbc;

	static int type=0;

	int kind = (type++)%3;
	
	if(kind==0) {
		program_alpha(bc);
	} else if(kind==1) {
		program_beta(bc);
	} else if(kind==2) {
		program_gamma(bc);
	}

	return 0;
}


