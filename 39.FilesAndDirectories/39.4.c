#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

static int depth = 0;

//递归的打印给定的目录下的所有文件和子目录的名称。
void tree(char *dirname) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    if ((dir = opendir(dirname)) == NULL) {
        fprintf(stderr, "Cannot open directory: %s\n", dirname);
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        char path[1024];
        sprintf(path, "%s/%s", dirname, entry->d_name);
        if (lstat(path, &statbuf) == -1) {
            fprintf(stderr, "Cannot stat %s\n", path);
            continue;
        }
        if (S_ISDIR(statbuf.st_mode)) {
            printf("%*s%s/\n", depth, "", entry->d_name);
            depth++;
            tree(path);
            depth--;
        } else {
            printf("%*s%s\n", depth, "", entry->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <dirname>\n", argv[0]);
        return 1;
    }
    tree(argv[1]);
    return 0;
}