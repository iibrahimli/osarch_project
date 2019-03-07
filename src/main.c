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
    char **    prog;    // program and its arguments to run


    // parse short arguments
    int option = 0;
    while((option = getopt(argc, argv, "+t:i:l:c")) != -1){
        switch (option){
            case 't':
                timefmt = optarg; printf("-t: %s\n", optarg); break;
            case 'i':
                interval = atoi(optarg); printf("-i: %s\n", optarg); break;
            case 'l':
                limit = atoi(optarg); printf("-l: %s\n", optarg); break;
            case 'c':
                chkexit = 1; printf("-c: set\n"); break;
            case '?':
                fatal_error("Invalid option"); break;
        }
    }

    // parse program and arguments for execvp
    prog = malloc(sizeof *prog * (argc-optind+1));
    for(int prog_idx=optind; prog_idx<argc; ++prog_idx){
        prog[prog_idx - optind] = argv[prog_idx];
    }
    prog[argc-optind] = NULL;

    return 0;
}