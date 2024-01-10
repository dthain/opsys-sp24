---
layout: default
title: Project 4 - 3D Printer Scheduler
---

# Project 4 - 3D Printer Scheduler

The goals of this project are:
- To demonstrate mastery of process and thread management.
- To practice working with synchronized data structures.
- To gain experience with asynchronous job scheduling.

Overview
--------

Consider what happens when you have a large number of jobs to accomplish,
but you cannot simply run them all at once simultaneously: downloading
lots of large files, sending models to a 3D-printer, rendering lots of
frames for a movie, processing credit card payments, etc.
To manage a large amount of work, you need a **job scheduler** which will
accept submissions, arrange for them to execute, and report back information
to ther user.

3D Printer Simulator
-------------------

In this project, you will build a job scheduler for a studio full
of 3D printers.  Such printers (as well as industrial CNC machines) take
input in the form of G-Code, a sequence of three dimensional drawing
instructions that looks like this:

```
G00 X246.00 Y250.00
G02 X254.00 Y250.00 I250.00 J250.00
G02 X246.00 Y250.00 I250.00 J250.00
G01 X262.75 Y250.00
G01 X262.75 Y472.63
G00 X258.75 Y472.63
. . .
```

Briefly, G00 indicates a fast repositioning move to an X Y position, G01 indicates a linear
movement at a standard feed rate, and G02 indicates a circular arc.  There
are many more codes, and you can read [more here](https://howtomechatronics.com/tutorials/g-code-explained-list-of-most-important-g-code-commands).
The complete sequence of commands draws something like this:

<img width="50%" src="circuit.png"/>

So that you don't have to carry around a bunch of printers, we will
give you a simulator `printsim` that reads simplified G-code and (gradually)
produces an image on the screen, instead of a printed object.
(It pauses a few moments at the end so that you can see the complete output.)
Of course, the printing still takes some time to complete.  Your job is to build
a scheduler that will keep several printers busy at once.

To begin, download the [printer simulator code](http://github.com/dthain/opsys-sp22/tree/main/project4/src), build it on the student
machines, and try out the examples given.  Write a simple G-code program
by hand that draws a shape or logo of some kind, and run it through
the simulator to get the idea.  Call this file `student.gcode` and
keep it so you can turn it in later.

(You are welcome to examine the simulator code,
but you won't need to change it for this assignment.)

The Printer Scheduler
---------------------

Your goal is to build a program called **printsched** for managing
multiple 3D printers.  When started, it should accept a fixed
number of printers to simulate as a command line argument.
Then, it should print out a prompt and wait for input from the user.
The available commands should be:

```
submit <file>
list
wait <jobid>
drain
remove <jobid>
hurry <jobid>
algo <fifo|sjf|balanced>
quit
help
```

The **submit** command defines a new print job, and names the gcode
file to execute on the printer.  **submit** should return immediately
and display a unique integer job ID generated internally by your program.
(Just start at one and count up.)  The job will then run in the background
when selected by the scheduler.  Each simulated printer will pop open a window and start drawing.

The **list** command lists all of the jobs currently known,
giving the job id, current state (WAITING, PRINTING, or DONE) and filename.
It should also state the average turnaround time and average response
time of all jobs in the DONE state.
You can format this output in any way that is consistent and easy to read.

The **wait** command takes a jobid and pauses until that job is
done printing.  Once complete, it should display the final status
of the job (success or failure) and the time at which it was submitted,
began printing, and completed.  (If the job was already complete,
then it should just display the relevant information immediately.)

The **drain** command should block until all jobs in the queue
are in the DONE state.

The **hurry** command should tag an existing job as an "important"
and cause it to be executed at the first opportunity, regardless
of the current scheduling algorithm.

The **remove** command takes a jobid and then removes it from
the queue.  However, a job cannot be removed if it is currently
in the PRINTING state. In this case, display a suitable error and
refuse to remove the job.

The **algo** command should select the scheduling algorithms
to be used by the printers: `fcfs` is first-come-first-served,
and `sjf` is shortest-job-first, and `balanced` should prefer
the shortest job, but make some accomodation to ensure that
no job is starved indefinitely.

The **quit** command should immediately exit the program,
regardless of any jobs in the queue.  (If end-of-file is detected
on the input, the program should quit in the same way.)

The **help** command should display the available commands
in a helpful manner.


Implementation Advice
---------------------

This project will bring together a variety of concepts that you have
studied so far: process management, thread synchronization,
and scheduling.  We aren't going to talk through every little function
you should use; you will need to review prior material and look up
documentation as needed.

Here is the basic architecture you should use:

<img width="100%" src="architecture.svg"/>

The program should consists of several threads: one main thread and several
printer threads, which interact through a common job queue.
The main thread interacts with the user by reading commands, submitting jobs to 
the queue, displaying status, and so forth.

Each printer is represented by a thread that works in the background.
Each thread should select the next job to run (based on the current scheduling
algorithm), render the print job by running the simulator program
as a separate external process, and then updating the job queue when that process is complete.

The tricky part of this assignment is the job queue itself.
The job queue should be implemented as a **monitor** as discussed
in class: a data structure that is protected by a **mutex**
and a **condition variable**.  The job queue should
only be accessed by functions that take care to use the mutex
for mutual exclusion and the condition variable to sleep and wakeup.

Generally speaking, the main thread should remain responsive to
the user by only performing quick actions on the job queue.
The user ought to be able to see immediate response to all commands,
except those that specifically wait for a job to complete.

Testing
-------

Test your scheduler carefully by using it to run a variety of jobs,
both short and long, in different orders.  Try different combinations
of operations: submitting, waiting, removing, etc.  Try the different
scheduling algorithms, and verify that the statistics reported are correct
for the jobs that actually run.  Try running with different numbers
of printers, and check that all are kept appropriately busy.
Think critically about unexpected
events, such as improper input from the user, incorrect arguments to
commands, and so forth.  Whenever such an unexpected event occurs,
you should display a detailed and helpful error message, and
(where possible) continue operation of the program.

A particularly useful  way to test is to create small input files
that contain a sequence of operations, for example create `test1.txt`
containing this:

```
submit student.gcode
list
wait 1
list
remove 1
list
quit
```

Then, just run your scheduler with input redirected from that file:
```
./printsched 3 < test1.txt
```

Turning In
----------

Please review the [general instructions](../general) for assignments.

Turn in the following:

- A gcode program of your own creation, called `student.gcode`
- All of your source code for `printsched` and `printsim`.
- A Makefile that builds `printsched` and `printsim` when the user types `make`, and cleans up all executables and object files on `make clean`.

This assignment is due at **5:00PM on Friday, March 25th**
To submit your files, make a directory called `project4` in
your dropbox, and copy your files there.

Grading
-------

Your grade will be based on:
- Correct implementation of each of the interactive commands.
- Correct behavior of the background printer threads.
- Correct synchronization techniques in the job queue.
- Good coding style, including clear formatting, sensible variable names, and useful comments.
