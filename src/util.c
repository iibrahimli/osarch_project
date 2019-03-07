#include <stdio.h>
#include <stdlib.h>
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