#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../include/util.h"


// default values for parameters
#define DEF_TIMEFMT  NULL
#define DEF_INTERVAL 10000
#define DEF_LIMIT    0
#define DEF_CHKEXIT  0



int main(int argc, char *argv[]){

    char *     timefmt  = DEF_TIMEFMT;
    useconds_t interval = DEF_INTERVAL * 1000;
    int        limit    = DEF_LIMIT;
    int        chkexit  = DEF_CHKEXIT;


    int option = 0;
    while((option = getopt(argc, argv, "+t:i:l:c")) != -1){
        switch (option){
            case 't':
                printf("-t: %s\n", optarg); break;
            case 'i':
                printf("-i: %s\n", optarg); break;
            case 'l':
                printf("-l: %s\n", optarg); break;
            case 'c':
                printf("-c: set\n"); break;
            case '?':
                fatal_error("Invalid option"); break;
        }
    }

    return 0;
}