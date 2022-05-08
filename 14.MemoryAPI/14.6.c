#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = malloc(sizeof(int) * 10);

    free(arr);

    printf("num: %d", arr[5]);
}

/*
 valgrind --leak-check=yes ./a.out
==266== Memcheck, a memory error detector
==266== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==266== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==266== Command: ./a.out
==266==
==266== Invalid read of size 4
==266==    at 0x1091B7: main (14.6.c:9)
==266==  Address 0x4a8d054 is 20 bytes inside a block of size 40 free'd
==266==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==266==    by 0x1091AE: main (14.6.c:7)
==266==  Block was alloc'd at
==266==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==266==    by 0x10919E: main (14.6.c:5)
==266==
num: 0==266==
==266== HEAP SUMMARY:
==266==     in use at exit: 0 bytes in 0 blocks
==266==   total heap usage: 2 allocs, 2 frees, 1,064 bytes allocated
==266==
==266== All heap blocks were freed -- no leaks are possible
==266==
==266== For lists of detected and suppressed errors, rerun with: -s
==266== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/