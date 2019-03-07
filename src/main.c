#include <unistd.h>
#include <stdlib.h>
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

#define OUT_BUF_SIZE (1<<16)


int main(int argc, char *argv[]){

    char *     timefmt  = DEF_TIMEFMT;
    useconds_t interval = DEF_INTERVAL * 1000;
    int        limit    = DEF_LIMIT;
    int        chkexit  = DEF_CHKEXIT;
    char **    prog;    // program and its arguments to run

    // buffers for program output and last output to be compared
    char *     out_buf      = calloc(OUT_BUF_SIZE, sizeof *out_buf);
    char *     last_out_buf = calloc(OUT_BUF_SIZE, sizeof *last_out_buf);


    // parse short arguments
    int option = 0;
    while((option = getopt(argc, argv, "+t:i:l:c")) != -1){
        switch (option){
            case 't':
                timefmt = optarg; break;
            case 'i':
                interval = atoi(optarg)*1000; break;
            case 'l':
                limit = atoi(optarg); break;
            case 'c':
                chkexit = 1; break;
            case '?':
                fatal_error("Invalid option"); break;
        }
    }

    // parse program and its arguments for execvp
    if(argc-optind == 0) fatal_error("No executable supplied");
    prog = malloc(sizeof *prog * (argc-optind+1));
    for(int prog_idx=optind; prog_idx<argc; ++prog_idx){
        prog[prog_idx - optind] = argv[prog_idx];
    }
    prog[argc-optind] = NULL;


    // execute program for limit iterations (indefinitely if limit == 0)    
    int prog_status, last_prog_status = 0;
    for(int iter = 0; iter < ((limit) ? limit : 1); iter += (limit) ? 1 : 0){
        printf("iter %d\n", iter);

        // print time if format string is set
        if(timefmt) print_time(timefmt);

        if(chkexit){
            // if detect should check the exit status, also compare with last exit status
            if((prog_status = run_prog(prog, out_buf, OUT_BUF_SIZE)) != last_prog_status){
                // print output buffer and continue to the next iteration
                printf("%s\n", out_buf);
                continue;
            }
            last_prog_status = prog_status;
        }

        // zero out the current output buffer
        memset(out_buf, 0, OUT_BUF_SIZE);
        last_prog_status = run_prog(prog, out_buf, OUT_BUF_SIZE);

        // check output 
        if(memcmp(out_buf, last_out_buf, OUT_BUF_SIZE)){
            // if output differs from the last output
            
        }


        usleep(interval);
    }


    return 0;
}