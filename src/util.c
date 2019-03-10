#include "../include/util.h"


void fatal_error(const char *cause){
    fprintf(stderr, "Error, exiting. Cause: %s\n", cause);
    exit(1);
}


void usage(void){
    printf("Usage: \n");
    printf("./detect [-t format] [-i interval] [-l limit] [-c] prog arg .. arg\n");
    printf("default values:\n"
           "\tinterval:    10000 ms\n"
           "\tlimit:       0\n"
           "\tc:           set\n"
           "\tformat:      not set\n");
}


int run_prog(char **prog, buffer *output_buf){
    int status=0;

     // create pipe for prog
    int fd[2];
    if(pipe(fd) == -1) fatal_error("could not create pipe");

    pid_t child = fork();
    switch(child){
        case -1:
            // error
            fatal_error("could not fork");
            break;
    
        case 0:
            // child
            dup2(fd[1], STDOUT_FILENO);

            close(STDERR_FILENO);
            close(fd[0]);
            close(fd[1]);

            // execute program with output redirected to the buffer
            execvp(prog[0], prog);
            break;
        
        default:
            // parent
            close(fd[1]);
            
            // read the output of the program into the buffer
            read_into_buffer(fd[0], output_buf);
            
            close(fd[0]);

            wait(&status);
            return WEXITSTATUS(status);
    }

    return 0;
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