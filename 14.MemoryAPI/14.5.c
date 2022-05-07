#include <stdlib.h>

int main() {
    int *arr = malloc(sizeof(int) * 100);
    arr[100] = 0;
}

/*
(gdb) run
Starting program: /xxx/14.MemoryAPI/a.out
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
[Inferior 1 (process 990) exited normally]

gdb依然未能提供任何有用的信息

valgrind --leak-check=yes ./a.out
==955== Memcheck, a memory error detector
==955== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==955== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==955== Command: ./a.out
==955==
==955== Invalid write of size 4
==955==    at 0x10916D: main (14.5.c:5)
==955==  Address 0x4a8d1d0 is 0 bytes after a block of size 400 alloc'd
==955==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==955==    by 0x10915E: main (14.5.c:4)
==955==
==955==
==955== HEAP SUMMARY:
==955==     in use at exit: 400 bytes in 1 blocks
==955==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
==955==
==955== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==955==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==955==    by 0x10915E: main (14.5.c:4)
==955==
==955== LEAK SUMMARY:
==955==    definitely lost: 400 bytes in 1 blocks
==955==    indirectly lost: 0 bytes in 0 blocks
==955==      possibly lost: 0 bytes in 0 blocks
==955==    still reachable: 0 bytes in 0 blocks
==955==         suppressed: 0 bytes in 0 blocks
==955==
==955== For lists of detected and suppressed errors, rerun with: -s
==955== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

不但检测出了非法的写，还检测出了未释放的内存
*/