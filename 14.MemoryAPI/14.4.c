#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int));
}

/*
  gdb:

  run
Starting program: /xxx/14.MemoryAPI/a.out
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
[Inferior 1 (process 945) exited normally]
查找不出任何问题
*/

/*
valgrind:

 valgrind --leak-check=yes ./a.out
==949== Memcheck, a memory error detector
==949== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==949== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==949== Command: ./a.out
==949==
==949==
==949== HEAP SUMMARY:
==949==     in use at exit: 4 bytes in 1 blocks
==949==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==949==
==949== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==949==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==949==    by 0x10915E: main (14.4.c:4)
==949==
==949== LEAK SUMMARY:
==949==    definitely lost: 4 bytes in 1 blocks
==949==    indirectly lost: 0 bytes in 0 blocks
==949==      possibly lost: 0 bytes in 0 blocks
==949==    still reachable: 0 bytes in 0 blocks
==949==         suppressed: 0 bytes in 0 blocks
==949==
==949== For lists of detected and suppressed errors, rerun with: -s
==949== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)


退出时堆的使用情况:  1个块，4个bytes
总体堆使用:  1次分配，0次释放，已分配4字节
一个块中的4个字节绝对丢失了
*/