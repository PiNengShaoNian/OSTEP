#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int fd[2];
    if(pipe(fd) < 0) {
        printf("pipe error\n");
        exit(1);
    }

    int pid = fork();
    if(pid == 0) {
        int ppid = fork();
        if(ppid == 0) {
            char *msg = "Hello!\n";
            write(fd[1], msg, strlen(msg));
        }
        else if(ppid > 0) {
            wait(NULL);
            char ans[10];
            int res = read(fd[0], ans, 10);
            printf("size: %d, %s\n", res, ans);
        }
    }

    return 0;
}