#include "../include/buffer.h"
#include "../include/util.h"


buffer create_buffer(){
    buffer r;
    r.size = 0;
    r.capacity = DEF_BUF_SIZE;
    r.data = calloc(DEF_BUF_SIZE, sizeof *r.data);
    if(!r.data) fatal_error("could not calloc buffer");
    return r;
}


int compare_buffers(const buffer *b1, const buffer *b2){
    if(b1->size == b2->size && !memcmp(b1->data, b2->data, b1->size)) return 0;
    else return 0;
}


void clear_buffer(buffer *b){
    b->size = 0;
    b->capacity = DEF_BUF_SIZE;
    b->data = realloc(b->data, DEF_BUF_SIZE);
    if(!b->data) fatal_error("could not realloc buffer");
}


void read_into_buffer(int fd, buffer *b){
    int rd;
    while((rd = read(fd, &b->data[b->size], b->capacity-b->size)) > 0){
        b->size += rd;
        if(b->capacity == b->size){
            b->capacity += BUF_GROW_SIZE;
            b->data = realloc(b->data, b->capacity);
            if(!b->data) fatal_error("could not grow (realloc) buffer");
        }
    }
}


void swap_buffers(buffer *b1, buffer *b2){
    static buffer tmp;
    tmp.size     = b2->size;
    tmp.capacity = b2->capacity;
    tmp.data     = b2->data;

    b2->size     = b1->size;
    b2->capacity = b1->capacity;
    b2->data     = b1->data;

    b1->size     = tmp.size;
    b1->capacity = tmp.capacity;
    b1->data     = tmp.data;
}


void destroy_buffer(buffer *b){
    b->size = 0;
    b->capacity = 0;
    b->data = NULL;
    free(b->data);
}