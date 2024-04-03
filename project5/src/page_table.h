/*
This is the interface to the page table module.
You should read it carefully but don't change it.
Make all of your changes in main.c instead.
*/

#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif

#define BIT_PRESENT 8
#define BIT_WRITE 4
#define BIT_REF   2
#define BIT_DIRTY 1

struct page_table;

typedef void (*page_fault_handler_t) ( struct page_table *pt, int page );

/*
Create a new page table, along with a virtual memory
that is "npages" big and a physical memory that is "nframes" big.
When a page fault occurs, the routine pointed to by "handler" will be called.
*/

struct page_table * page_table_create( int npages, int nframes, page_fault_handler_t handler );

/* Delete a page table and the corresponding virtual and physical memories. */

void page_table_delete( struct page_table *pt );

/*
Set the frame number and access bits associated with a page.
The bits may be any of BIT_PRESENT, BIT_WRITE, BIT_DIRTY, or BITREF. logical-ored together.
*/

void page_table_set_entry( struct page_table *pt, int page, int frame, int bits );

/*
Get the frame number and access bits associated with a page.
"frame" and "bits" must be pointers to integers which will be filled with the current values.
The bits returned may be any combination of BIT_PRESENT, BIT_WRITE, BIT_DIRTY, and BIT_REF.
*/

void page_table_get_entry( struct page_table *pt, int page, int *frame, int *bits );

/* Return a pointer to the start of the virtual memory associated with a page table. */

void * page_table_get_virtmem( struct page_table *pt );

/* Return a pointer to the start of the physical memory associated with a page table. */

void * page_table_get_physmem( struct page_table *pt );

/* Return the total number of frames in the physical memory. */

int page_table_get_nframes( struct page_table *pt );

/* Return the total number of pages in the virtual memory. */

int page_table_get_npages( struct page_table *pt );

/* Print out the page table entry for a single page. */

void page_table_print_entry( struct page_table *pt, int page );

/* Print out the state of every page in a page table. */

void page_table_print( struct page_table *pt );

/*
Manually set the reference or dirty bits.  This is a hack needed by our
simulated programs b/c the posix interface doesn't track reference and dirty.
You do not need to use this function in your assignment.
*/

void __internal_set_bits( struct page_table *pt, void *vaddr, int bits );

#endif
