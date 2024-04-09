---
layout: default
title: Project 6: Buffer / Cache
---

# WARNING: Under Construction

**This is an old version of an assignment, and currently being revised.  If you got here by accident, don't use this document yet!**

# Project 6: Buffer / Cache

## Objectives

By undertaking this project, you will:
- learn how to implement a core operating system capability.
- learn about the scheduling and performance aspects of disk I/O.
- gain more experience in writing synchonized multi-threaded code.
- develop your expertise in C programming by using structures and pointers extensively.

**This project may be done in pairs or singletons.**
Please submit your work to a single dropbox with a PARTNERS file
that indicates the project members.  Both partners will receive the same grade.

Over the course of the semester, the projects
have grown in both size and difficulty.  This project is the
largest of all, so don't leave it to the last minute.
**Get started right away!**

## Overview

In this project, you will build a buffer/cache for an operating system.
This will be a challenging but fun project which will help to reveal
the inner workings of the OS, and shows the importance of managing
memory as part of I/O performance.  We will provide you with several programs
that make disk requests, a simulated disk that satisfies those
requests, and your job is to build the buffer/cache module that
sits in the middle.    This figure gives the overall idea:

![](overview.png)

At the top are a large number of programs running concurrently
and accessing the disk in different patterns:some sequentially,
some random, and some in concentrated areas.  These programs
will make their requests known by calling the functions
`bcache_read()` and `bcache_write()`.

In the middle is the buffer/cache, the part that you will create.
This module implements the functions `bcache_read` and `bcache_write`,
which both operate by manipulating the actual buffer data structure.
It consists of a number of 4KB blocks of memory, each representing
one block of data, in one of several states.  The buffer/cache has
two combined jobs:

1 - It **buffers** blocks when they are written, so that the writing
process may return quickly, and the data may be written to disk as time permits.

2 - It **caches** recently accessed data in memory, so that processes
that return to the same data may access it at memory speed, instead of waiting for the dis.

Note that `bcache_read` and `bcache_write` operate only on the
buffer data structure, they do not access the actual underlying disk.
That is the job of the **I/O scheduler thread** which runs in the background.
It considers the current state of the data structure, and performs
the actual `disk_read` and `disk_write` operations according to one of
several scheduling policies, updating the buffer structure as needed.

Finally at the bottom is the simulated disk, which is very similar
to the one you used in the virtual memory project.  It has the (simple)
capabilities of a real disk, allowing you only to read and write one
whole block at a time.  Only one thread (the I/O scheduler) can access
the disk at a time, and this is the performance bottleneck of the system.
Each request to the disk will take at least 10ms, plus a little more
for the distance that the disk must travel since the last request.

## Buffer / Cache Implementation

As in previous projects, the buffer/cache is at heart a **data structure**
protected by a **monitor** (mutex and condition variables).
Each block stored in the cache will consist of 4KB of the actual data,
along with some additional values to indicate *which* block number it
corresponds to on the disk, and the current state of the block.

Programs will access the buffer/cache using the following three operations:
```
int bcache_read( struct bcache *bc, int blocknum, char *data );
int bcache_write( struct bcache *bc, int blocknum, const char *data );
int bcache_drop( struct bcache *bc, int blocknum );
```

As the name suggests, `bcache_read` should read a 4KB block from disk
into the buffer/cache, then copy the 4KB cached data into the `data` pointer
provided by the caller.  `bcache_write` should copy 4KB from the `data` pointer
into the buffer/cache, and arrange for it to be written back to disk as time
permits.  `bcache_drop` indicates that the given block number is no longer
needed, and the cache may drop it.
These three functions do not access the disk directly, but should modify
the state of the buffer cache, and (possibly) wait for the I/O scheduler
thread to take some action before returning.

The I/O scheduler thread running in the background does not interact
with the caller directly, but should examine the state of the buffer
cache, decide what action needs to be taken on a particular block,
and then perform `disk_read` or `disk_write` as needed to carry
out the action.

You will need to record the current state of each block in the cache,
and we suggest that you use the following state machine:

![](states.png)

`WANTREAD`
indicates a block that has been requested by `bcache_read` and is not
yet fulfilled. `READING` indicates a block that is currently being
read in by the I/O scheduler thread.  `READY` indicates a block that
has been read into the buffer/cache and is ready to be used immediately.
`DIRTY` indicates a block that has been modified by `bcache_write`.
`WRITING` indicates a block that is currently being written to disk
by the I/O scheduler thread.  Once a block has been written, it is now
clean and goes back to the `READY` state.

## Example Operation

Here is an example of a few operations on the buffer/cache to give the idea.
Suppose that we start with a completely empty buffer.
Process P1 acts first, issuing a `bcache_read` on block 10.
Because that block is not (yet) in the cache, the buffer cache reacts
by creating a new block in memory in the `WANTREAD` state.  `bcache_read` then
waits for the I/O scheduler thread to take action.  The scheduler thread
notices the waiting block, and takes action by changing it to the `READING`
state, and issues the `disk_read` operation, which may take some time.

![](example1.png)

While the I/O scheduler thread is busy reading (and P1 is waiting),
P2 goes about its business and issues a `bcache_write` operation on block 25.
The buffer cache accepts this new block, and makes a copy of it in the buffer cache.
It begins in the `DIRTY` state, because it reflects data that has not yet
been written to disk.  `bcache_write` can return immediately, trusting that
the I/O scheduler thread will (eventually) write the block to disk.
P2 then repeats this action on blocks 26 and 27.

![](example2.png)

Finally, the I/O scheduler completes the `disk_write` operation, and marks
block 10 as `READY`.  It notifies the waiting thread that the block is now
ready, and the corresponding `bcache_read` operation completes, so that P1
can go about its further business.

![](example3.png)

Next, the I/O scheduler looks for more work to do.  It notices that Block 25
is dirty, so it changes its state to `WRITING` and calls `disk_write` to copy
it back to the disk.  In the meantime, P2 calls `bcache_read` on block 10.
Block 10 is already in the buffer/cache, and so it can be provided to P2 immediately
without waiting for the I/O scheduler thread.  In a similar way, P3 calls `bcache_read`
to read block 27, which is also present and can be provided immediately.

![](example4.png)

Eventually, the I/O scheduler thread completes working on Block 25,
and marks it as `READY`, because it is no longer dirty.  The scheduler thread
looks for more work to do, and selects block 26.  It changes the state to
`WRITING` and calls `disk_write` as appropriate.  Meanwhile, P3 calls `bcache_read`
to read block 17, which is not in the cache, and so it blocks in the `WANTREAD` state.

![](example5.png)

## Things to Figure Out

This project will require that you work out several important details
in order to get a correct result.  We won't tell you exactly how to go
about it (since there are multiple good solutions) but these are some
areas that you will need to ponder.

**Thread Synchronization** - The programs and the I/O scheduler will
run as concurrent threads, all attempting to modify the buffer/cache
data structure simultaneously.  Use what you have learned about threads
and synchronization to make sure that this is done safely, while still
permitting independent actions to proceed concurrently.

**Replacement Policy** - The buffer/cache has a maximum number of blocks
it can hold.  When the cache becomes full, you must select some block to
remove, so that you can allocate space for a new one.  Be sure to do so
safely, so that you don't yank away a block in the middle of an access.

**Scheduling Policy** - The I/O scheduler thread will continually select
a new block to act on after completing its current action.  Which is the
best block to select?  Keep in mind that the disk will operate more quickly
if it doesn't have to travel as far between operations.

**Corner Cases** - Each `bcache_read` or `bcache_write` may encounter
a block in any one of the states given above.  Take the time to consider
every single state and think through what should happen when a `bcache_read`
or `bcache_write` encounters a block in that state.

## Getting Started

Download the [source code](http://github.com/dthain/opsys-sp22/tree/main/project6/src) and build it with `make`.

The system is invoked as follows:

```
./bcache <nthreads> <buffer-blocks> <disk-blocks>
```

For example, to run with 5 threads, 10 buffer blocks in memory, and 100 disk blocks:

```
./bcache 5 10 100
```

As provided, the system will actually run correctly, although very slowly.
We have provided you with a "dummy" implementation of the buffer cache,
in which `bcache_read` and `bcache_write` are implemented by calling
`disk_read` and `disk_write` directly.  The result is that each program
will perform I/O in a blocking manner and run **very** slowly.
By implementing the buffer cache correctly, you will get this system
to run **much**faster.

At the end of the run, the main program will print out some key
performance metrics, simply counting the number of buffer and
disk operations over the elapsed time, like this:

```
 buffer  reads:
 buffer writes:
 buffer  drops:
   disk  reads:
   disk writes:
  elapsed time:
   buffer perf: 3.4 buffer ops/s
     disk perf: 3.4 buffer ops/s
```

Note that the disk will always be less than 100 ops/s,
because each operation takes (at least) 10ms.
But, by making effective use of the buffer cache,
you should be able to get the buffer performance **much** higher
than 100 ops/s.
And, by scheduling the I/O thread carefully, you should
be able to get the disk performance very close to 100 ops/s.

How fast can you make it go?

## Turning In

Please review the [general instructions](general.md) for assignments.

This projects is due at **11:59PM on Wednesday April, 30th**.  Late assignments are not accepted.  (And it's also the end of the semester!)

You should turn the following to **one** of the partner's dropboxes:
- All of your source code.
- A `Makefile` that builds the code.
- A `PARTNERS` file indicating the names of both partners.
- A `RESULTS` file containing the plain text results of the following commands:
```
./bcache 5 10 100
./bcache 50 10 100
./bcache 5 20 100
./bcache 50 20 100
```

Please do not turn in executables, disk images, or other files.
As a reminder, your dropbox directory is:

```
/escnfs/courses/sp24-cse-30341.01/dropbox/YOURNAME/project6
```

