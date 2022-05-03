#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    int n;
    printf("输入运行系统调用次数：");
    scanf("%d", &n);

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < n; ++i) {
        read(0, NULL, 0);
    }
    gettimeofday(&end, NULL);
    printf("执行时间为: %f微秒\n", (float)((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec) / n));
    return 0;
}