
# Project 1: System Calls and Error Checking

First, read the [general instructions](general) for assignments. Make sure you are using the correct compiler on the correct machine.

This project is a warm up assignment for the course. The basic concept is very simple: to write a program that copies files and directories from one place to another. However, the main challenge of engineering operating systems is dealing with errors and unexpected conditions. Thus, the main focus of this assignment will be on the correct handling of errors. The goals of this project are:

- To review your knowledge of basic C programming.
- To learn the most essential Unix system calls.
- To gain experience in rigorous error handling.

## Part 1: File Copy

Write a C program called filecopy which duplicates a file from one place to another. The program will be invoked as follows:

```
filecopy SourceFile TargetFile
```

If successful, the program should output the total number of bytes copied:

```
filecopy: copied 23847 bytes from ABC to XYZ
```

If not successful, it should print a suitable error message, like this:

```
filecopy: couldn't open ABC: No such file or directory.
```

(But read the rest of the assignment below before completing Part 1.)

## Part 2: Recursive Copy

Write a C program called treecopy which duplicates a directory tree from one place to another. The program will be invoked as follows:

```
treecopy SourcePath TargetPath
```

treecopy must create an exact copy of SourcePath under the new name TargetPath. If the source path is just a file, then a simple file copy takes place in the same way as filecopy But if it is a directory, then the entire directory and its contents should be copied recursively. As the program runs, it should output what is being copied:

```
source -> target
source/x -> target/x
source/y -> target/y
source/y/z -> target/y/z
...
```

Upon successful completion, treecopy should report the total directories, files, and bytes copied, and exit with result 0. For example:

```
treecopy: copied 5 directories, 34 files, and 238475 bytes from ABC to XYZ
```

If treecopy encounters eny kind of error or user mistake, it must immediately stop and emit a message that states the program name, the failing operation, and the reason for the failure, and then exit with result 1. For example:

```
treecopy: couldn't create file mishmash: Permission Denied.
treecopy: couldn't open directory foobar: File Exists.
treecopy: couldn't write to file bizbaz: Disk Full.
```

If the program is invoked incorrectly, then it should immediately exit with a helpful message:

```
treecopy: Too many arguments!
usage: treecopy <sourcefile> <targetfile>
```

**Special Cases:** If the destination path already exists, or the source contains something other than a directory or file, then treecopy should halt without copying anything more and display a suitable error message.

In short, there should be no possible way to invoke the program that results in a segmentation fault, a cryptic message, or a silent failure. Either the program runs successfully to completion, or it emits a helpful and detailed error message to the user.

## System Calls

To carry out this assignment, you will need to learn about the following system calls:

```
open, creat, read, write, close, stat, mkdir, opendir, closedir, readdir, strerror, errno, exit
```

Manual pages ("man pages") provide the complete reference documentation for system calls. They are available on any Linux machine by typing man with the section number and topic name. Section 1 is for programs, section 2 for system calls, section 3 for C library functions. For example man 2 open gives you the man page for open. You can also use this online service which has the same information.

As you probably already know, man pages are a little difficult to digest, because they give complete information about one call, but not how they all fit together. However, with a little practice, you can become an expert with man pages. Consider the man page for open. At the top, it tells you what include files are needed in order to use open:

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

## How to Copy a File

Copying a file from one place to another is a little more complex than it first appears. Because a file may be very large (possibly larger than all available memory), you cannot expect to load it all into memory at once, and then write it out. Instead, the file must be copied in chunks: read one chunk from the source into memory, write it out to the destination, and keep going until the whole file is copied. (The exact size of the chunk isn't critical, but 4KB is a good round number, for reasons we will discuss later in the semester.)

So, the general strategy is this:

```
open the source file
open the destination file

char buffer[4096]

loop {
    read a chunk from the source into the buffer
    write a chunk from buffer into the destination
}

close the source file
close the destination file
```

However, it's not quite that simple. The read and write system calls have some unusual behavior. If you request to read count bytes of data like this:

```
int result = read(fd,buffer,count);
```

There are several possible outcomes. If read was able to access some data, it will return the number of bytes actually read. The number might be as high as count, but it could also be smaller. For example, if you request to read 4096 bytes, but there are only 40 bytes remaining in the file, read will return 40. If there is nothing more left in the file, read will return zero. If there is an error, the result will be less than zero, as above. write operates in a very similar way.

So, to copy a file carefully, you will need to do something like this:

```
loop over {
     read a chunk of data from the source file
     if there was an error reading, exit with an error
     if no data left, end the loop

     write a chunk of data to the target file
     if not all the data was written, try the remainder.
     if there was an error writing, exit with an error
}
```

## Testing

Make sure to test your program on a wide variety of conditions. Start by testing single files, both small and large. How do you know if the file copy worked correctly? Use the program md5sum to take the checksum of both files, and double check that it matches:

```
% md5sum /tmp/SourceFile
b92891465b9617ae76dfff2f1096fc97  /tmp/SourceFile
% md5sum /tmp/TargetFile
b92891465b9617ae76dfff2f1096fc97  /tmp/TargetFile
```

Then, move to testing a directory with a few small entries. If that works, try directories nested several levels deep. If that works, then try copying some system directores like /usr/local or /etc. Make sure to delete your copies when you are done, so as not to waste space.

## Grading
Your grade will be based on:
- Single file copy. (20%)
- Recursive directory copy. (40%)
- Correct handling of all error conditions. (30%)
- Good coding style, such as clear formatting, sensible variable names, and useful comments. (10%)

## Turning In

This assignment is due on Friday, January 21st at 5:00PM.

Please turn in only the source code files filecopy.c and treecopy.c and a Makefile that builds both executables. Do not submit executables or other files, since we will build your code from source.

Your dropbox is mounted on the student machines at this location:

```
/escnfs/courses/sp22-cse-30341.01/dropbox/YOURNETID
```

To submit your files, make a directory called project1 in your dropbox, and copy your files there:

```
mkdir /escnfs/courses/sp22-cse-30341.01/dropbox/YOURNETID/project1
cp filecopy.c /escnfs/courses/sp22-cse-30341.01/dropbox/YOURNETID/project1
cp treecopy.c /escnfs/courses/sp22-cse-30341.01/dropbox/YOURNETID/project1
cp Makefile /escnfs/courses/sp22-cse-30341.01/dropbox/YOURNETID/project1
```

And double check that the right items are present:

```
ls -la /escnfs/courses/sp22-cse-30341.01/dropbox/YOURNETID/project1
```
