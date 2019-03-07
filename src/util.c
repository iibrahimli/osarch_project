#include "../include/util.h"


void fatal_error(const char *cause){
    fprintf(stderr, "Error, exiting. Cause: %s\n", cause);
    exit(1);
}


void usage(void){
    printf("Usage: \n");
    printf("./detect [-t format] [-i interval] [-l limit] [-c] prog arg .. arg\n");
    printf("default values:\n\
    interval: 10000 ms\n\
    limit: 0\n\
    c: set\n\
    format: not set\n");
}


int run_prog(char **prog, char *output_buf, int buf_size){
    int status;

    return WEXITSTATUS(status);
}


void print_time(char *fmt){
    if(!fmt) return;
    char tstr[64];
    time_t rawtime;
    time(&rawtime);
    struct tm* info = localtime(&rawtime);
    strftime(tstr, 64, fmt, info);
    printf("%s\n", tstr);
}


void swap_buffers(char *b1, char *b2){
    char *temp;
    temp = b2;
    b2 = b1;
    b1 = temp;
}