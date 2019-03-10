#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <fcntl.h>


#define DEF_BUF_SIZE  1024
#define BUF_GROW_SIZE 512


// output buffer that holds output of the program
// dynamically grows, holds size of used segment
typedef struct bf {
    size_t size;       // # of bytes actually used in data
    size_t capacity;   // total memory allocated to data
    char *data;
} buffer;


// creates and returns an empty buffer
buffer create_buffer();


// returns 1 if the buffers are the same, 0 otherwise
int compare_buffers(const buffer *b1, const buffer *b2);


// clears contents of a buffer, resets it to default size
void clear_buffer(buffer *b);


// reads from FD into B, growing B if needed
void read_into_buffer(int fd, buffer *b);


// swaps the contents of the buffers
void swap_buffers(buffer *b1, buffer *b2);


// destructor
void destroy_buffer(buffer *b);


#endif