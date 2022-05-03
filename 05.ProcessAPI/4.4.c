#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
  int pid = fork();
  char *cmd = "/bin/ls";
  char *arg[] = {"ls", "-a", NULL};

  if (pid < 0) {
    printf("fork error\n");
    exit(1);
  } else if (pid == 0) {
    //    exec不会返回,所以第一条execl语句后的语句不会被执行
    execl(cmd, "ls", NULL);
    execlp(cmd, "ls", NULL);
    execve(cmd, arg, envp);
    execv(cmd, arg);
    execvp(cmd, arg);
    execle(cmd, "ls", NULL, envp);
  } else {
  }
  return 0;
}


// 答: exec 多个变体提供不同的功能,

// 在 exec 函数族中，后缀 l、v、p、e 添加到 exec 后，所指定的函数将具有某种操作能力：

// l: 希望接收以逗号分隔的参数列表,列表以 NULL 指针作为结束标志
// v: 希望接收一个以 NULL 结尾字符串数组的指针
// p: 是一个以 NULL 结尾的字符串数组指针,函数可以利用 DOS 的 PATH 变量查找自程序文件
// e 函数传递指定采纳数 envp(环境变量),允许改变子进程环境,无后缀 e 是,子进程使用当前程序环境
// c 语言没有默认参数语法,只能实现多个变体