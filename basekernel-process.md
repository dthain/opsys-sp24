# Bonus Info: Basekernel Process Implementation

**(This is not required information, but may be of interest if you want to explore more.)**

Here are some places in [Basekernel](https://github.com/dthain/basekernel)
where you can see how processes are implemented.

- [kernel/process.h](https://github.com/dthain/basekernel/blob/master/kernel/process.h) describes the states of a process, and `struct process` is the equivalent of the Process Control Block (PCB).
- [kernel/process.c](https://github.com/dthain/basekernel/blob/08be8c66d3dd39ec539ed45c3a38a932617349d6/kernel/process.c#L22) contains the `current` pointer to the currently-running process, as well as the `ready_list` of processes, and the `grave_list` of completed processes.
- [process_switch](https://github.com/dthain/basekernel/blob/master/kernel/process.c#L22) has the (surprisingly simple) context switch code, which pushes all the current registers, switches the stack pointer, selects a new process, and then pops all the registers.  Note that this (simple) kernel just runs whatever process is next in the list.
