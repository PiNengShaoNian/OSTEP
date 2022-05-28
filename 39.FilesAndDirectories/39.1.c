#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

void println_file_type(__mode_t mode) {
    if (S_ISREG(mode)) {
        printf("regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("directory\n");
    } else if (S_ISCHR(mode)) {
        printf("character device\n");
    } else if (S_ISBLK(mode)) {
        printf("block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("fifo\n");
    } else if (S_ISLNK(mode)) {
        printf("symbolic link\n");
    } else if (S_ISSOCK(mode)) {
        printf("socket\n");
    } else {
        printf("unknown\n");
    }
}

int main(int argc, char **argv) {
    if(argc <= 1) {
        printf("Usage: %s <file>\n filename or dirname", argv[0]);
        return 1;
    }

    struct stat buf;
    assert(stat(argv[1], &buf) == 0);
    printf("filename: %s\n", argv[1]);
    println_file_type(buf.st_mode);
    printf("last modified: %s\n", ctime(&buf.st_mtime));
    printf("last accessed: %s\n", ctime(&buf.st_atime));
    printf("last changed: %s\n", ctime(&buf.st_ctime));
    printf("uid: %d\n", buf.st_uid);
    printf("gid: %d\n", buf.st_gid);
    printf("device: %ld\n", buf.st_dev);
    printf("inode: %ld\n", buf.st_ino);
    printf("mode: %d\n", buf.st_mode);
    printf("number of hard links: %ld\n", buf.st_nlink);
    printf("blocks: %ld\n", buf.st_blocks);
    printf("block size: %ld\n", buf.st_blksize);
    printf("number of bytes: %ld\n", buf.st_size);
    return 0;
}