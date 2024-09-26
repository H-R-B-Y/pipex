

Allowed Functions:
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid

prinf or alternatives.

## perror
```c
#include <stdio.h>
void perror(const char *s);
```
The perror() function produces a message on standard error
describing the last error encountered during a call to a system
or library function.

First (if s is not NULL and *s is not a null byte ('\0')), the
argument string s is printed, followed by a colon and a blank.
Then an error message corresponding to the current value of errno
and a new-line.

## strerror
```c
#include <string.h>
char *strerror(int errnum);
```
The strerror() function returns a pointer to a string that
describes the error code passed in the argument errnum

## access
```c
#include <unistd.h>
int access(const char *pathname, int mode);
```
access() checks whether the calling process can access the file pathname. If pathname is a symbolic link, it is dereferenced.

The mode specifies the accessibility check(s) to be performed, and is either the value `F_OK`, or a mask consisting of the bitwise OR of one or more of `R_OK`, `W_OK`, and `X_OK`. `F_OK` tests for the existence of the file. `R_OK`, `W_OK`, and `X_OK` test whether the file exists and grants read, write, and execute permissions, respectively.

## dup dup2
```c
#include <unistd.h>
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```
These system calls create a copy of the file descriptor oldfd.

dup() uses the lowest-numbered unused descriptor for the new descriptor.

dup2() makes newfd be the copy of oldfd, closing newfd first if necessary, but note the following:
- If oldfd is not a valid file descriptor, then the call fails, and newfd is not closed.
- If oldfd is a valid file descriptor, and newfd has the same value as oldfd, then dup2() does nothing, and returns newfd.

On success, these system calls return the new descriptor. On error, -1 is returned, and errno is set appropriately.


## execve
```c
#include <unistd.h>
int execve(const char *filename, char *const argv[], char *const envp[]);
```
execve() executes the program pointed to by filename. filename must be either a binary executable, or a script starting with a shebang `#!{path to interpreter}`.

argv is an array of argument strings passed to the new program. By convention, the first of these strings should contain the filename associated with the file being executed. envp is an array of strings, conventionally of the form key=value, which are passed as environment to the new program. Both argv and envp must be terminated by a NULL pointer. 

execve() does not return on success, and the text, data, bss, and stack of the calling process are overwritten by that of the program loaded.

on error -1 is returned, and errno is set appropriately.


## exit
```c
#include <stdlib.h>
void exit(int status);
```
Same as python.

## fork
```c
#include <unistd.h>
pid_t fork(void);
```
The fork() function shall create a new process. The new process (child process) shall be an exact copy of the calling process (parent process) except as detailed below: (see man for full list)
- The child process shall have a unique process ID.
- The child process ID also shall not match any active process group ID.
- The child process shall have a different parent process ID, which shall be the process ID of the calling process.
- The child process shall have its own copy of the parent's file descriptors. Each of the child's file descriptors shall refer to the same open file description with the corresponding file descriptor of the parent.
- The child process shall have its own copy of the parent's open directory streams. Each open directory stream in the child process may share directory stream positioning with the corresponding directory stream of the parent.
- Any semaphores that are open in the parent process shall also be open in the child process.

Upon successful completion, fork() shall return 0 to the child process and shall return the process ID of the child process to the parent process. Both processes shall continue to execute from the fork() function. Otherwise, -1 shall be returned to the parent process, no child process shall be created, and errno shall be set to indicate the error.

## pipe
```c
#include <unistd.h>
int pipe(int fildes[2]);
```
The pipe() function shall create a pipe and place two file descriptors, one each into the arguments fildes[0] and fildes[1], that refer to the open file descriptions for the read and write ends of the pipe. Their integer values shall be the two lowest available at the time of the pipe() call.

Data can be written to the file descriptor fildes[1] and read from the file descriptor fildes[0]. A read on the file descriptor fildes[0] shall access data written to the file descriptor fildes[1] on a first-in-first-out basis. It is unspecified whether fildes[0] is also open for writing and whether fildes[1] is also open for reading.

Upon successful completion, 0 shall be returned; otherwise, -1 shall be returned and errno set to indicate the error.



## wait waitpid
```c
#include <sys/wait.h>
pid_t wait(int *stat_loc);
pid_t waitpid(pid_t pid, int *stat_loc, int options);
```
The wait() and waitpid() functions shall obtain status information pertaining to one of the caller's child processes. Various options permit status information to be obtained for child processes that have terminated or stopped. If status information is available for two or more child processes, the order in which their status is reported is unspecified.

The waitpid() shall suspend execution of the calling thread until status information for the pid and options arguments.

- If pid is greater than 0, it specifies the process ID of a single child process for which status is requested.
- If pid is 0, status is requested for any child process whose process group ID is equal to that of the calling process.
