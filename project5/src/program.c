/*
Do not modify this file.
Make all of your changes to main.c instead.
*/

#include "program.h"

#include <stdio.h>
#include <stdlib.h>

static int compare_bytes( const void *pa, const void *pb )
{
	unsigned char a = *(unsigned char*)pa;
	unsigned char b = *(unsigned char*)pb;

	if(a<b) {
		return -1;
	} else if(a==b) {
		return 0;
	} else {
		return 1;
	}

}

void alpha_program( unsigned char *data, int length )
{
	unsigned long total=0;
	int i,j;

	printf("alpha: initializing memory\n");
	for(i=0;i<length;i++) {
		data[i] = 0;
	}

	printf("alpha: modifying memory...\n");

	for(j=0;j<100;j++) {
		int start = j*4096;
		int chunksize = 10*4096;

		for(i=0;i<chunksize;i++) {
			data[ (start+i) % length ] = i;
		}
	}

	printf("alpha: summing up results\n");
	for(i=0;i<length;i++) {
		total += data[i];
	}

	printf("alpha: result is %lu\n",total);
}

void beta_program( unsigned char *data, int length )
{
	unsigned total = 0;
	int i;

	srand48(4856);

	printf("beta: initializing memory\n");

	for(i=0;i<length;i++) {
		data[i] = lrand48();
	}

	printf("beta: sorting memory\n");
	qsort(data,length,1,compare_bytes);

	printf("beta: adding up all values\n");
	for(i=0;i<length;i++) {
		total += data[i];
	}

	printf("beta result is %u\n",total);

}

void gamma_program( unsigned char *data, int length )
{
	unsigned i, j;
	unsigned char *a = data;
	unsigned char *b = &data[length/2];
	unsigned total = 0;

	printf("gamma: initializing two large vectors\n");

	for(i=0;i<length/2;i++) {
		a[i] = i%256;
		b[i] = i%171;
	}

	for(j=0;j<10;j++) {
		printf("gamma: computing dot product\n");
		for(i=0;i<length/2;i++) {
			total += a[i]*b[i];
		}
	}

	printf("gamma: result is %u\n",total);
}

void delta_program( unsigned char *data, int length )
{
	unsigned i;
	unsigned total = 0;

	srand48(30341);

	printf("delta: initializing memory\n");
	for(i=0;i<length;i++) {
		data[i] = i*2;
	}

	printf("delta: swapping random locations\n");
	for(i=0;i<100000;i++) {
		int a = lrand48()%length;
		int b = lrand48()%length;
		int t = data[a];
		data[a] = data[b];
		data[b] = t;
	}

	printf("delta: adding up all values\n");
	for(i=0;i<length;i++) {
		total += data[i];
	}

	printf("delta: result is %u\n",total);
}
