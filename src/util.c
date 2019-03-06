#include <stdio.h>
#include <stdlib.h>
#include "../include/util.h"


void fatal_error(const char *cause){
    fprintf(stderr, "Error, exiting. Cause: %s\n", cause);
    exit(1);
}


void usage(void){
    printf("Usage: ");
}