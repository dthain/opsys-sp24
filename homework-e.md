# Homework E - Memory System Organization

For problems 1-4 draw a **neat detailed sketch** of the described
situation.  Practice doing all computations easily and quickly using [metric units](metric.md)
as we have done in class.  The size of all objects should be written as a small number
accompanied by appropriate binary metric units.  For example, write `4MB` and not `2^32 bytes`.

1 - Consider a **segmented** memory space with a 24 bit virtual address, 24 bit physical address,
and a max of 32 segments per process.  Sketch the translation of virtual to physical addresses as we have done in class. Make sure to include:
- The number of bits in each field.
- The number of elements in each table.
- The total size (in bytes) of each table.
- The maximum possible **segment** size.
- The maximum possible physical memory.

2 - Consider a **paged** memory space with a **single level** table,
using a 36 bit virtual address, a 24-bit physical address, and a 1KB page size.
Sketch the translation of virtual to physical addresses as we have done in class.
Make sure to include:
- The number of bits in each field.
- The number of elements in each table.
- The total size (in bytes) of each table.
- The maximum possible virtual memory.
- The maximum possible physical memory.

3 - Consider a **paged** memory space with a **multi level** table
but otherwise the same parameters as the previous question.
Sketch the translation of virtual to physical addresses as we have done in class.
Make sure to include:
- The number of bits in each field.
- The number of elements in each table.
- The total size (in bytes) of each table.
- The maximum possible virtual memory.
- The maximum possible physical memory.

4 - Suppose you have **paged** memory space with a **multi level** table
using a 48 bit virtual address, a 36 bit physical address, and 32KB page size.
Sketch the translation of virtual to physical addresses as we have done in class.
Make sure to include:
- The number of bits in each field.
- The number of elements in each table.
- The total size (in bytes) of each table.
- The maximum possible virtual memory.
- The maximum possible physical memory.

5 - Suppose that you have a paged virtual memory system consisting of 128GB of
main memory with a 120ns access time, 4KB sized pages, a 1TB SSD with a 50us access time,
and a MMU implementing a three level page table with a 16-entry TLB and a 20ns lookup time.

(a) What is the Effective Access Time (EAT) of this system, assuming 90% of accesses hit the TLB,
9.9% of accesses hit main memory, and 0.1% of accesses hit the SSD?

(b) Which of the following upgrades would provide the best performance? (1) Increase the TLB hit rate to 95%.  (2) Replace the main memory with faster chips that have a 60ns access time.  (3) Replace the SSD with a faster model that has a 25us access time.  Justify your answer.

(c) The operating system must maintain a bitmap tracking frames in physical
memory, just to keep track of which ones are in use or available.
Each bit in the bitmap indicates whether one specific page is used or available.
How many frames must be set aside to store this bitmap?

Take a snapshot of your answers and upload to Canvas as a PDF or JPG files.
