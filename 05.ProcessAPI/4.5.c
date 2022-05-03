#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if(pid < 0) {
        perror("fork");
        exit(1);
    }
    else if(pid == 0) {
        int res = wait(NULL);
        printf("child %d\n", res);
        printf("child\n");
    }
    else {
        int pid = wait(NULL);
        printf("parent %d\n", pid);
    }

    return 0;
}

// 答:

// wait 成功返回子进程 id,执行失败返回-1

// 子进程调用 wait,执行失败,返回-1