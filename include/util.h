#ifndef UTIL_H
#define UTIL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "buffer.h"


// reports a fatal error with CAUSE and
// exits the program with exit code 1 
void fatal_error(const char *cause);


// prints usage
void usage(void);


// runs PROG in a child process, waiting for
// its exit. writes output into OUTPUT_BUF and
// returns the child's exit code
int run_prog(char **prog, buffer *output_buf);


// prints current date and time if FMT != NULL,
// nothing otherwise
void print_time(char *fmt);


#endif // UTIL_H