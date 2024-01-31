# The Basics of the GNU Debugger

## What is GDB?

GDB, or GNU Debugger, is a powerful and widely used debugger for software development. This is the formal and professional definition of GDB, and it pretty much sums up what GDB is, but GDB is more than that. I’d argue GDB is the way out of working on an assignment late into the AMs, dealing with the mid-assignment sessions where I question my major, and skipping events to go out because I’m slumped with work.

Before I go on claiming gdb is this amazing tool that will solve all your problems, I’m going to jump into how this software works. The only assumption here is that work will be done on the student machines which have gdb installed.

### BEFORE USING GDB

Please compile your C program with the -g flag.

```bash
gcc -Wall -Werror -pedantic-errors **-g** prog1.c -o prog1
```

### 1) To Start Running GDB

Just type gdb and the name of the executable you’re trying to debug, and you’re already on your way to finding that bug that has wasted a little more time than it should have.

```bash
gdb <executable>: Start GDB and load the specified executable.
gdb --args <executable> arg1 arg2 arg3

EX: gdb ./a.out
EX: gdb --args ./a.out OS 30341 arg3
```

### 2) To Quit & Kill GDB

If you already really really hate this and just want to end it (please don’t), just enter **quit** and answer yes to the question “quit anyway?” if prompted 😞 The **kill** command terminates the program being debugged.

```bash
(gdb) quit 
(gdb) kill 
```

### 3) Set a Breakpoint

You may already know, or at least have an idea of where your code is breaking. It’s not the **int a = 5;** in the first line of your main function. It’s probably somewhere in that recursive function you called that keeps throwing a segault. Breakpoints are a great way to tell gdb: run normally up until you reach a function **func** or ****some line number where the breakpoint was placed, but once you make it there, STOP EXECUTING.

If you’re not sure what’s happening in your code and don’t want to set a breakpoint, that’s fine. We can walk through the whole program from start to finish! You can skip this step.

```bash
(gdb) break function_name
(gdb) break file1.c:6
```

### 4) To Run & to Continue

You already set your breakpoint. Enter run and the program will start running normally until it reaches a breakpoint if it exists, else the program just runs normally. The continue command continues execution until the next breakpoint if there are multiple breakpoints.

```bash
(gdb) run

(gdb) continue
```

### 5) To Start

GDB will throw some information at you after completing step 1), but to get started, just enter the command **start**. This is useful if you did not set up a breakpoint and want to go over the program from the start of the main function, step by step.

```bash
(gdb) start
```

<aside>
💡 Before going into the next part of this tutorial, it would be nice to know what to expect from gdb once it starts cooking. Most of the time, gdb is going to show you the line of code you’re at. If you set a breakpoint at the function **factorial** called somewhere in the main function and enter run, the first thing you pop up is the first line in that factorial function. Example below.

</aside>

```bash
factorial (name=0x7fffffffd694 nbr=5) at test.c:10
10           if(nbr == 1){
```

## To Solve the Problem

Everything above is important to know, but we haven’t solved anything yet. It may look like a lot of information so far, but it’s not that much. Start gdb with the executable and its command line arguments if they exist, set some breakpoints and press run, or just enter start and get going.

We need gdb to help us walk through the program line by line and figure out where the point of failure is, and luckily we have the two commands **step** and **next.**

### Step & Next

These two commands are simple. **Next** executes the next line of code without stepping into functions, while **Step** executes the next line of code and steps into functions. When to use one over the other? I’ll give some examples

Let’s say we complete steps 1) and 5) that are discussed above. We run gdb on an executable and enter start. This means it will start debugging from the first line in main which is the code below.

```bash
int fileDescriptor = open("file.txt", O_WRONLY);
```

GDB will tell us that this is the first line we are dealing with, and at that point we can enter a command to tell it what to do next. What do you think makes more sense here, to step or to next? We probably don’t need to see every line of code in the **open** function, so using **next** may be the better option. **Next** will execute the function on the current line without stepping into it. GDB will then move to the next line in the current scope we’re in.

For the code snippet below, it would make sense to step into a function we defined and look for the point of failure in our code. If we are confident that **my_factorial_func** is not the point of failure, we can just enter **next** and move on to the next line.

```bash
int result = my_factorial_func(10);
```

### **Examining Variables**

We are segfaulting in a while loop that prints out all the elements in a linked list. As far as we know, the loop should print out all 5 elements containing values 1 through 5, but it keeps breaking at element 3. We decide that before we go into the third iteration where it is breaking, we want to print out the values stored in our pointers and see what’s up. So, at the second iteration we can use the commands below.

```bash
(gdb) info locals
(gdb) print <variable>
```

**Print** prints the value of a variable.

**Info** **locals** shows local variables in the current stack frame.

Example:

```bash
(gdb) break main
Breakpoint 1 at 0x...
(gdb) run
Starting program: /path/to/your/my_program

Breakpoint 1, main () at my_program.c:5
5       int x = 42;
(gdb) print x
$1 = 42
(gdb) print pi
$2 = 3.14159
(gdb) print message
$3 = "Hello, GDB!"
(gdb) print x
$4 = (int *) 0xABCDEFG
(gdb) print x->next
$5 = 0x0
```

These commands are useful to understand the stage we are at in our code and what our variables are looking like. Our goal is to detect something fishy.

### Miscellaneous

- **`list [function]`**: Display source code around the current line or specified function.
- **`info breakpoints`**: Show information about breakpoints.
- **`info threads`**: Display information about threads.

## Summary

I’m writing this as a person who avoided GDB at all costs. I go way back with print statements and they have served me well. We’ve been friends and still are. But, there are times when GDB or just a debugger in general is necessary. You can get away without a debugger for so long until your manager at your internship sees you using print statements. It wasn’t until I was bullied into using a debugger that I came to realize that my stubbornness was an issue. Just like any tool, it isn’t perfect, nor is it suitable to fix every single problem, but no doubt it is a valuable tool that any serious programmer must have in their back pocket.
