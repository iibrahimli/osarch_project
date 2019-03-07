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

#define OUT_BUF_SIZE (1<<17)


int main(int argc, char *argv[]){

    char *     timefmt  = DEF_TIMEFMT;
    useconds_t interval = DEF_INTERVAL * 1000;
    int        limit    = DEF_LIMIT;
    int        chkexit  = DEF_CHKEXIT;
    char **    prog;    // program and argument vector

    // buffers for program output and last output to be compared
    // these buffers act like the frame buffers in double buffered rendering
    // one of them points to current buffer where the program output is written
    // the other one points to last output to compare with current output
    // and they are swapped on every iteration
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
    // check arguments
    if(interval <= 0) fatal_error("Interval should be positive");
    if(limit < 0) fatal_error("Limit should be non-negative");


    // parse program and its arguments
    // a NULL-terminated argument vector is prepared for execvp 
    if(argc-optind == 0) fatal_error("No executable supplied");
    prog = malloc(sizeof *prog * (argc-optind+1));
    for(int prog_idx=optind; prog_idx<argc; ++prog_idx){
        prog[prog_idx - optind] = argv[prog_idx];
    }
    prog[argc-optind] = NULL;


    // execute program for limit iterations (indefinitely if limit == 0)    
    int prog_status, last_prog_status = 0;
    for(int iter = 0; iter < ((limit) ? limit : 1); iter += (limit) ? 1 : 0){
        printf("--------- iter %d ---------\n", iter);

        // printf("=== out_buf ===\n");
        // printf("%s\n", out_buf);
        // printf("=== last_out_buf ===\n");
        // printf("%s\n", last_out_buf);
        // print time if format string is set
        if(timefmt) print_time(timefmt);

        if(chkexit){
            memset(out_buf, 0, OUT_BUF_SIZE);            
            // if detect should check the exit status, also compare with last exit status
            if((prog_status = run_prog(prog, out_buf, OUT_BUF_SIZE)) != last_prog_status){
                // print output buffer and continue to the next iteration
                printf("%s\n", out_buf);
                printf("exit: %d\n", prog_status);
                swap_buffers(out_buf, last_out_buf);
                usleep(interval);
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
            printf("%s\n", out_buf);

            // swap buffers for next iteration
            swap_buffers(out_buf, last_out_buf);
        }

        // sleep between iterations
        usleep(interval);
    }


    free(prog);
    free(out_buf);
    free(last_out_buf);

    return 0;
}