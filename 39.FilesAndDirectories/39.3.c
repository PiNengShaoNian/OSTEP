#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/sendfile.h>

int main(int argc, char* argv[]) {
    int fd, n = 10;
    fd = open(argv[1], O_RDONLY);
    n = atoi(argv[2]);

    off_t size = lseek(fd, 0, SEEK_END);     // 可以把文件指针移动到文件末尾, 返回值是文件首部到尾部的偏移量
    off_t offset = 0;
    char ch;
    while (lseek(fd, -1, SEEK_CUR) >= 0 && n > 0) {
        read(fd, &ch, 1);   // read会让文件指针向后移动一位
        offset = lseek(fd, -1, SEEK_CUR);
        if (ch == '\n') 
            --n;
    }
    if (n == 0) ++offset;   // 跳过一个回车符

    lseek(fd, offset, SEEK_SET);
    while(read(fd, &ch, 1) > 0) {
        printf("%s", &ch);
    }

    close(fd);
    return 0;
}