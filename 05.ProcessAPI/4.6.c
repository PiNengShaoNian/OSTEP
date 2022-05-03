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
        sleep(1);
        printf("child\n");
    }
    else {
        int res = waitpid(pid, NULL, 0);
        printf("parent %d\n", res);
    }

    return 0;
}

// 　wait会令调用者阻塞直至某个子进程终止；

// 　waitpid则可以通过设置一个选项来设置为非阻塞，另外waitpid并不是等待第一个结束的进程而是等待参数中pid指定的进程。