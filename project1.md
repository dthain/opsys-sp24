
# Project 1: System Calls and Error Checking

First, read the [general instructions](general) for assignments. Make sure you are using the correct compiler on the correct machine.

This project is a warm up assignment for the course. The basic concept is simple: write a program that summarizes the contents
of a directory in the filesystem, recursively.  However, the main challenge of engineering operating systems is dealing with errors and unexpected conditions. Thus, the main focus of this assignment will be on the correct handling of errors. The goals of this project are:

- To review your knowledge of basic C programming.
- To learn the most essential Unix system calls.
- To gain experience in rigorous error handling.

## Part 1: Directory List

Write a C program called `dirlist` that shows the contents of a directory.
The program will be invoked like this:

```
./dirlist <pathname>
```

If successful, the program should display information about each file in that directory,
showing the type, name, size (in bytes), access mode (in octal) and owners name (in text).
Make sure to arrange the display nicely in columns, something like this:

```
% ./dirlist $HOME
NAME             SIZE    TYPE MODE OWNER
-----------------------------------------
program.c        3264 B  file 0644 dthain
test               32 B  dir  0755 dthain
homework.doc     7585 B  file 0644 dthain
courses            16 B  link 0600 dthain
-----------------------------------------
```

Upon successful completion, `dirlist` should report the total directories, files, and symlinks encountered, and exit with status zero.

```
dirlist: 34 files, 5 directories, and 3 symlinks
```

If `dirlist` encounters eny kind of error or user mistake, it must immediately stop and emit a message that states the program name, the failing operation, and the reason for the failure, and then exit with result 1. For example:

```
dirlist: couldn't open file mishmash: Permission Denied.
dirlist: couldn't stat directory zibzab: No such file or directory.
dirlist: couldn't allocate memory: Out of memory
```

If the program is invoked incorrectly, then it should immediately exit with a helpful message:

```
dirlist: Too many arguments!
usage: dirlist <path>
```

In short, there should be no possible way to invoke the program that results in a segmentation fault, a cryptic message, or a silent failure. Either the program runs successfully to completion, or it emits a helpful and detailed error message to the user.

## Part 2: Recursive Listing

Once you have `dirlist` working nicely, then make a new program called `treelist`
by copying `dirlist.c` into `treelist.c`.  Modify `treelist` so that it shows more
detail for each item:

- If the item is a file, then load the first 40 characters of the file into memory,
and print them at the end of the line.  To keep the display readable, don't print
newlines or any unprintable characters that may occur.  (See isprint(3))

- If the item is a symbolic link, use `readlink` to obtain the target path of the link,
and display that.

- If the item is a directory, then display the contents of that directory recursively
and clearly indented. Of course, if there are directories within directories (of arbitrary depth)
then those should be displayed with additional indentation as appropriate.  (And you
should skip over the special entries `.` and `..` so as not to recurse endlessly.)

For example, your display may look something like this:

```
% ./treelist $HOME
NAME             SIZE    TYPE MODE    OWNER CONTENTS
--------------------------------------------------------------------------------
program.c        3264 B  file 0644   dthain /* Program 1 for CSE 30341 */
test               32 B  dir  0755   dthain 
> data1.txt      32767 B  file 0644   dthain This is dataset #1 with dates...
> data2.txt      15687 B  file 0644   dthain This is dataset #2 without dates...
homework.txt     7585 B  file 0644   dthain HW1 for CSE 30341 due on 01/01/2029
courses            16 B  link 0600   dthain -> /some/other/dir
--------------------------------------------------------------------------------
```

Just like `dirlist`, `treelist` should also handle error conditions with informative messages.

## System Calls

To carry out this assignment, you will need to learn about the following system calls, and perhaps others:

```
opendir, closedir, readdir, stat, lstat, readlink
open, read, close, getpwuid, strerror, errno, exit
```

Manual pages ("man pages") provide the complete reference documentation for system calls. They are available on any Linux machine by typing man with the section number and topic name. Section 1 is for programs, section 2 for system calls, section 3 for C library functions. For example man 2 open gives you the man page for open.   There are also a variety of online services ([linux.die.net](https://linux.die.net/man/2)) that provide the same information.

As you probably already know, man pages are a little difficult to digest, because they give complete information about one call, but not how they all fit together. However, with a little practice, you can become an expert with man pages. Consider the [man page for open(2)](https://linux.die.net/man/2/open). At the top, it tells you what include files are needed in order to use open:

```
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
```

It also gives the the prototype for several variations of the system call:

```
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
int creat(const char *pathname, mode_t mode);
```

The documentation contains many more details than you need, but it is usually a good bet to read the first paragraph, and then skim ahead until you find what you are looking for. It is also always fruitful to read the RETURN VALUE section, and to use the SEE ALSO section to look up related system calls.

## Handling Errors

An operating system (and any program that deals with it) must be vigilant in dealing with errors and unexpected conditions. End users constantly attempt operations that are illegal or make no sense. Digital devices behave in unpredictable ways. So, when you write operating system code, you must always check return codes and take an appropriate action on failure.

How do you know if a system call succeeded or failed? In general read the RETURN VALUE section of the manual page, and it will tell you exactly how success or failure is indicated. However, nearly all Unix system calls that return an integer (open, read, write, close, etc.) have the following convention:
- If the call succeeded, it returns an integer greater than or equal to zero.
- If the call failed, it returns an integer less than zero, and sets the global variable errno to reflect the reason for the error.

And, nearly all C library calls that return a pointer (malloc, fopen, etc.) have a slightly different convention:
- If the call succeeded, it returns a non-null pointer.
- If the call failed, it returns null, and sets the global variable errno to reflect the reason for the error.

The errno variable is simply an integer that explains the reason behind an errno. Each integer value is given a macro name that makes it easy to remember, like EPERM for permission denied. All of the error types are defined in the file /usr/include/asm/errno.h. Here are a few of them:

```
#define EPERM            1      /* Operation not permitted */
#define ENOENT           2      /* No such file or directory */
#define ESRCH            3      /* No such process */
#define EINTR            4      /* Interrupted system call */
...
```

You can check for specific kinds of errors like this:

```
fd = open(filename,O_RDONLY,0);
if(fd<0) {
    if(errno==EPERM) {
        printf("Error: Permission Denied\n");
    } else {
        printf("Some other error.\n");
        ...
    }
    exit(1);
}
```

This would get rather tedious with 129 different error messages. Instead, use the strerror routine to convert errno into a string, and print out a descriptive message like this:

```
fd = open(filename,O_RDONLY,0);
if(fd<0) {
     printf("Unable to open %s: %s\n",filename,strerror(errno));
     exit(1);
}
```

## Some Hints

- You may need to put `#define _GNU_SOURCE` at the top of your programs (above the `#includes`)
in order to access all of the relevant system calls.
- See the `stat(2)` man page and read about the macros `S_ISDIR`, `S_ISREG`, etc. which determine
whether an entry is a directory, file, etc...
- Note the difference between `stat(2)` and `lstat(2)`: one follows symbolic links and the other does not.
- See `printf(3)` for many different ways of arranging output, justifying left and right, etc.
- See `isprint(3)` for a listing of many functions that determine whether a character is printable, whitespace, numeric, etc...
- See `getpwuid(3)` for converting an integer `uid` into information about a user.

## Testing

Make sure to test your program on a wide variety of conditions. Start by testing small directories, like your own home directory, and compare the output to what you get from `ls -l`.  Then move on to trying various kinds of system directories like `/etc` and `/home`.  Of course, it is likely that you won't have permission to access all of those directories, and your tools should stop with useful error messages.  If your program really gets stuck in an infinite loop, kill it with Control-C.

## Grading
Your grade will be based on:
- Correctness of `dirlist`. (40%)
- Correctness of `treelist`. (30%)
- Correct handling of all error conditions. (20%)
- Good coding style, such as clear formatting, sensible variable names, and useful comments. (10%)

## Turning In

This assignment is due on Friday, January 16th at 11:59PM.

Review the [general instructions](general) for assignments.

Please turn in only the source code files `dirlist.c` and `treelist.c` and a `Makefile` that builds both executables. Do not turn in executables or other files, since those just take up space, and we will build your code from source anyway.
