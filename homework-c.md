# Homework C - Scheduling

# Part 1 - Scheduling Archetypes
----------------------------------
Suppose that you have the following jobs to schedule
in a single-processor operating system.

|      | Arrival Time | Length |
|------|----|----|
|Job A | 0  | 10 |
|Job B | 5  | 20 |
|Job C | 8  | 5  |
|Job D | 12 | 3  |
|Job E | 20 | 2  |
|Job F | 26 | 8  |

**Question 1** : For the First Come First Served (FCFS) (non-preemptive) scheduling algorithm, show the following:

- (a) A timeline showing the order in which each job executes.
- (b) The response time and turnaround time of each job.
- (c) The average response time and average turnaround time across all jobs.
- (d) The utilization of the system over the entire schedule.

You may assume that each context switch takes one time unit,
and that ties are broken in favor of the job that arrived earlier.

**Question 2** : Repeat for the Shortest Job First (SJF) (non-preemptive) scheduling algorithm.

**Question 3** : Repeat for the Shortest Completion Time First (SCTF) (preemptive) scheduling algorithm.

# Part 2 - Multi Level Feedback Queue

Suppose that you have a single processor multi-level-feedback-queue
as described in Chapters 8.1 and 8.2.  (Do not add the later extra rules.)
There are three queues with scheduling quanta of 5, 10, and 20 time units.
Each context switch takes one time unit.  (This includes when a single
job changes queues but continues to execute.) Ties are broken in favor of
the job that arrived earlier.

Consider the following three jobs:

- Job A wants to run continuously for 25 time units starting at time 0.
- Starting at time 5, Job B wants to run for 1 time unit, then block for 11 time units, repeating three times.
- Starting at time 18, Job C wants to run continuously for 10 time units

**Question 4**: Carefully diagram how the basic MLFQ scheduler would schedule these jobs until all are complete,
including the times of each significant event in the schedule.

# Turning In

These problems involve working out a number of diagrams,
so we suggest that you sketch your answers carefully on
paper, take a photo and then upload to Canvas.

