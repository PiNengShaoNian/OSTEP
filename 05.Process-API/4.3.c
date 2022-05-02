#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int pid = vfork();
    if(pid < 0) {
        perror("vfork");
        exit(1);
    }
    else if(pid == 0) {
        printf("Hello!\n");
        exit(0);
    }
    else {
        printf("Goodbye\n");
    }

    return 0;
}