#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../include/buffer.h"
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
    char **    prog;    // program and argument vector

    // buffers for program output and last output to be compared
    // these buffers act like the frame buffers in double buffered rendering.
    // one of them points to current buffer where the program output is written
    // the other one points to last output to compare with current output
    // and they are swapped every iteration
    buffer     out_buf      = create_buffer();
    buffer     last_out_buf = create_buffer();


    // parse short arguments
    int option = 0;
    while((option = getopt(argc, argv, "+t:i:l:c")) != -1){
        switch (option){
            case 't':
                timefmt = optarg;
                break;
            case 'i':
                interval = atoi(optarg)*1000;
                break;
            case 'l':
                limit = atoi(optarg);
                break;
            case 'c':
                chkexit = 1;
                break;
            case '?':
                fatal_error("invalid option");
                break;
        }
    }

    // check arguments
    if(interval <= 0) { fatal_error("interval should be positive"); usage(); }
    if(limit < 0) { fatal_error("limit should be non-negative"); usage(); }


    // parse program and its arguments
    // a NULL-terminated argument vector is prepared for execvp
    if(argc-optind == 0) { fatal_error("no executable supplied"); usage(); }
    prog = malloc(sizeof *prog * (argc-optind+1));
    for(int prog_idx=optind; prog_idx<argc; ++prog_idx){
        prog[prog_idx - optind] = argv[prog_idx];
    }
    prog[argc-optind] = NULL;


    // execute program for limit iterations (indefinitely if limit == 0)    
    int prog_status, last_prog_status = 0;
    int iteration = 0;
    while(limit == 0 || iteration < limit){

    }

    // deallocate memory
    free(prog);
    destroy_buffer(&out_buf);
    destroy_buffer(&last_out_buf);

    return 0;
}