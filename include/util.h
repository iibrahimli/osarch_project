#ifndef UTIL_H
#define UTIL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>


// reports a fatal error and exits the program
// with exit code 1 (all errors are passed to this f)
void fatal_error(const char *cause);


// prints usage
void usage(void);


// runs program in a child process, waiting for its exit.
// writes output into output_buf, and returns exit code
int run_prog(char **prog, char *output_buf, int buf_size);


// prints current date and time if fmt != NULL, nothing otherwise
void print_time(char *fmt);


// swaps pointers to buffers
void swap_buffers(char *b1, char *b2);


#endif // UTIL_H