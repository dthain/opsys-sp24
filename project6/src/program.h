#ifndef PROGRAM_H
#define PROGRAM_H

#include "disk.h"

void * program_thread( void *bc );

void program_fill_disk( struct disk *d );

#endif
