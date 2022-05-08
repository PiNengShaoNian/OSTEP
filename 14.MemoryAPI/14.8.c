#include "stdio.h"
#include "stdlib.h"

#define INIT_SIZE 10
#define EXTEND_SIZE 5

typedef struct Vector {
    float *x;
    float *y;
    int length;
    int max_length;
} Vector;

int v_append(Vector *, float, float);
void v_free(Vector *);

int main() {
    Vector *v = malloc(sizeof(Vector));
    v->x = malloc(sizeof(float) * INIT_SIZE);
    v->y = malloc(sizeof(float) * INIT_SIZE);
    v->length = 0;
    v->max_length = INIT_SIZE;

    v_append(v, 1.0, 2.0);
    printf("(x,y): (%f, %f)\n", v->x[0], v->y[0]);
    v_free(v);
    return 0;
}

int v_append(Vector *v, float x, float y) {
    if (v->length == v->max_length) {
        v->max_length += EXTEND_SIZE;
        v->x = realloc(v->x, sizeof(float) * v->max_length);
        v->y = realloc(v->y, sizeof(float) * v->max_length);
    }

    v->x[v->length] = x;
    v->y[v->length] = y;
    v->length++;
    return v->length;
}

void v_free(Vector *v) {
    free(v->x);
    free(v->y);
    free(v);
}

/*
 valgrind --leak-check=yes ./a.out
==329== Memcheck, a memory error detector
==329== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==329== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==329== Command: ./a.out
==329==
(x,y): (1.000000, 2.000000)
==329==
==329== HEAP SUMMARY:
==329==     in use at exit: 0 bytes in 0 blocks
==329==   total heap usage: 4 allocs, 4 frees, 1,128 bytes allocated
==329==
==329== All heap blocks were freed -- no leaks are possible
==329==
==329== For lists of detected and suppressed errors, rerun with: -s
==329== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/