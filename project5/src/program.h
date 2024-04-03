/*
Do not modify this file.
Make all of your changes to main.c instead.
*/

#ifndef PROGRAM_H
#define PROGRAM_H

#include "page_table.h"

void alpha_program( struct page_table *pt, unsigned char *data, int length );
void beta_program( struct page_table *pt, unsigned char *data, int length );
void gamma_program( struct page_table *pt, unsigned char *data, int length );
void delta_program( struct page_table *pt, unsigned char *data, int length );

#endif
