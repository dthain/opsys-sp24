/*
These are the sample programs that modify memory.
Do not modify this file.
Make all of your changes to main.c instead.
*/

#define _XOPEN_SOURCE

#include "program.h"
#include "page_table.h"

#include <stdio.h>
#include <stdlib.h>

void alpha_program( struct page_table *pt, unsigned char *data, int length )
{
	unsigned long total=0;
	int i,j;

	printf("alpha: initializing memory\n");
	for(i=0;i<length;i++) {
		data[i] = 0;
		__internal_set_bits(pt,&data[i],BIT_REF|BIT_DIRTY);
	}

	printf("alpha: modifying memory...\n");

	for(j=0;j<100;j++) {
		int start = j*4096;
		int chunksize = 10*4096;

		for(i=0;i<chunksize;i++) {
			data[ (start+i) % length ] = i;
			__internal_set_bits(pt,&data[ (start+i) % length ],BIT_REF|BIT_DIRTY);
		}
	}

	printf("alpha: summing up results\n");
	for(i=0;i<length;i++) {
		total += data[i];
		__internal_set_bits(pt,&data[i],BIT_REF);
	}

	printf("alpha: result is %lu\n",total);
}

void recurse( struct page_table *pt, unsigned char *a, int length, int depth )
{
	int i;
	for(i=0;i<length;i++) {
		a[i] = depth;
		__internal_set_bits(pt,&a[i],BIT_REF|BIT_DIRTY);
	}
	
	if(length>1) {
		recurse(pt,&a[0],length/2,depth+1);
		recurse(pt,&a[length/2],length/2,depth+1);
	}
}
             
void beta_program( struct page_table *pt, unsigned char *data, int length )
{
	unsigned total = 0;
	int i;

	printf("beta: traversing memory recursively\n");
	recurse(pt,data,length,1);

	printf("beta: adding up all values\n");
	for(i=0;i<length;i++) {
		total += data[i];
		__internal_set_bits(pt,&data[i],BIT_REF);
	}

	printf("beta result is %u\n",total);

}

void gamma_program( struct page_table *pt, unsigned char *data, int length )
{
	unsigned i, j;
	unsigned char *a = data;
	unsigned char *b = &data[length/2];
	unsigned total = 0;

	printf("gamma: initializing two large vectors\n");

	for(i=0;i<length/2;i++) {
		a[i] = i%256;
		__internal_set_bits(pt,&a[i],BIT_REF|BIT_DIRTY);
		b[i] = i%171;
		__internal_set_bits(pt,&b[i],BIT_REF|BIT_DIRTY);
	}

	for(j=0;j<10;j++) {
		printf("gamma: computing dot product\n");
		for(i=0;i<length/2;i++) {
			total += a[i]*b[i];
			__internal_set_bits(pt,&a[i],BIT_REF);
			__internal_set_bits(pt,&b[i],BIT_REF);
		}
	}

	printf("gamma: result is %u\n",total);
}

void delta_program( struct page_table *pt, unsigned char *data, int length )
{
	unsigned i;
	unsigned total = 0;

	srand48(30341);

	printf("delta: initializing memory\n");
	for(i=0;i<length;i++) {
		data[i] = i*2;
		__internal_set_bits(pt,&data[i],BIT_REF|BIT_DIRTY);
	}

	printf("delta: swapping random locations\n");
	for(i=0;i<100000;i++) {
		int a = lrand48()%length;
		int b = lrand48()%length;
		int t = data[a];
		__internal_set_bits(pt,&data[a],BIT_REF);
		data[a] = data[b];
		__internal_set_bits(pt,&data[b],BIT_REF);
		__internal_set_bits(pt,&data[a],BIT_REF|BIT_DIRTY);
		data[b] = t;
		__internal_set_bits(pt,&data[b],BIT_REF|BIT_DIRTY);
	}

	printf("delta: adding up all values\n");
	for(i=0;i<length;i++) {
		total += data[i];
		__internal_set_bits(pt,&data[i],BIT_REF);
	}

	printf("delta: result is %u\n",total);
}
