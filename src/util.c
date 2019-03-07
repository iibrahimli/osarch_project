#include "../include/util.h"
#include "../include/buffer.h"


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


int run_prog(char **prog, buffer *output_buf){
    int status=0;
    int rd;

    int fd[2];
    if(pipe(fd) == -1) fatal_error("Could not create pipe");

    pid_t child = fork();
    switch(child){
        case -1:
            // error
            fatal_error("Could not fork");
            break;
    
        case 0:
            // child
            dup2(fd[1], STDOUT_FILENO);
            close(STDERR_FILENO);
            close(fd[0]);
            close(fd[1]);
            execvp(prog[0], prog);
            break;
        
        default:
            // parent
            close(fd[1]);
            rd = read(fd[0], output_buf, buf_size);
            if(rd < buf_size) output_buf[rd] = '\0';
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


void swap_buffers(char *b1, char *b2){
    char *temp;
    temp = b2;
    b2 = b1;
    b1 = temp;
}