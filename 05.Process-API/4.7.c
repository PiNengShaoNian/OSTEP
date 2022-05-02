#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();
    if(pid < 0) {
        printf("fork error\n");
        exit(1);
    }
    else if(pid == 0) {
        close(STDOUT_FILENO);
        printf("child\n");
    }
    else {
        int res = wait(NULL);
        printf("parent %d\n", res);
    }
}

//关闭后子进程中的printf 不会打印到控制台

