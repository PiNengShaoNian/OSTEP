#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = malloc(sizeof(int) * 10);
    free(&arr[5]);

    printf("num: %d\n", arr[5]);
}

/*
./a.out
free(): invalid pointer
Aborted
*/