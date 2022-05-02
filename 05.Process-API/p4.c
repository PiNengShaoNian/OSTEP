#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if(rc == 0) {
        close(STDOUT_FILENO);
        int fd = open("./p4.out", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        if(fd < 0) {
            fprintf(stderr, "open failed\n");
            exit(1);
        }
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: "wc" (word count)
        myargs[1] = strdup("p3.c"); // argument: file to count
        myargs[2] = NULL; // end of args
        execvp("wc", myargs); // execute "wc"
    }
    else {
        int wc = wait(NULL);
    }

    return 0;
}