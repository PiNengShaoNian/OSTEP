#define _GNU_SOURCE
#include "sched.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/time.h"
#include "unistd.h"

int main() {
    int fd1[2], fd2[2], fdt[2], pid, n;

    struct timeval start, end;

    const struct sched_param param = {sched_get_priority_min(SCHED_FIFO)};
    cpu_set_t set;
    // 将cpu 0添加到集合
    CPU_SET(0, &set);

    printf("输入测试次数(次数太少会导致误差极大): ");
    scanf("%d", &n);

    if(pipe(fd1) < 0 || pipe(fd2) < 0 || pipe(fdt) < 0) {
        printf("pipe error\n");
        exit(1);
    }

    if((pid = fork()) < 0) {
        printf("fork error\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) {
        //需要root权限
        //SCHED_FIFO指定先来调度服务
        if(sched_setscheduler(getpid(), SCHED_FIFO, &param) < 0) {
            printf("程序运行需要root权限， sched_setscheduler error\n");
            exit(EXIT_FAILURE);
        }

        //进程绑定核心
        if(sched_setaffinity(getpid(), sizeof(set), &set) < 0) {
            printf("程序运行需要root权限， sched_setaffinity error\n");
            exit(EXIT_FAILURE);
        }

        gettimeofday(&start, NULL);
        for(int i = 0; i < n; ++i) {
            read(fd1[0], NULL, 0);
            write(fd2[1], "h", 1);
        }

        write(fdt[1], &start, sizeof(struct timeval));
        exit(EXIT_SUCCESS);
    }
    else {
        if(sched_setscheduler(getpid(), SCHED_FIFO, &param) < 0) {
            printf("程序运行需要root权限， sched_setscheduler error\n");
            exit(EXIT_FAILURE);
        }

        //进程绑定核心
        if(sched_setaffinity(getpid(), sizeof(set), &set) < 0) {
            printf("程序运行需要root权限， sched_setaffinity error\n");
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < n; ++i) {
            write(fd1[1], "h", 1);
            read(fd2[0], NULL, 0);
        }

        gettimeofday(&end, NULL);

        read(fdt[0], &start, sizeof(struct timeval));
        printf("上下文切换时间为: %f 微秒",
               (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / 2 / n);
    }
}