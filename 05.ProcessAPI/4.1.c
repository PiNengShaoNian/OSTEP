#include <stdio.h>
#include <sys/wait.h>
// #include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   int x = 0;
   x = 100;
   int rc = fork();

   if(rc == 0) {
       printf("child, x: %d\n", x);
       x = 0;
   }
   else {
       wait(NULL);
       printf("parent, x: %d\n", x);
   }
}

//答: 子进程父进程各自一份 x 变量,修改互不影响

