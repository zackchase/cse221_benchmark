#include <time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define THRESHOLD 10000000000000000
#define ITERATIONS 1000
#define EXPONENT 20

static __inline__ unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

int *makeArray(int exp) {
    int *arr;
    arr = (int*)malloc((1 << exp) * sizeof(int));
    int i;
    int *head = (int*)arr;
    int *p = head;
    // printf("arr address %p\n", arr);
    for (i = 0; i < (1 << exp); i++) {
        p = &arr[i];
        arr[i] = rand() % (1 << exp);
        // printf("value at arr[%d]: %d at addr %p\n", i, arr[i], &arr[i]);
    }

    return arr;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int i;
    int n = 26;
    // int n = 5;

    int **p_int = (int**)malloc(n * sizeof(int*));
    // printf("address of p_int: %p\n", p_int );
    for (i = 0; i < n; i++) {
        p_int[i] = makeArray((i+3));
        // printf("address of ptr to size %d: %p\n", (1 << (i+2)), (int*)p_int[i] );
        // // printf("value of blah: %d\n", (int)p_int[i][rand() % (1 << (i+2))]);
    }

    float total_diff = 0;
    int iter = 0;
    long long start, end;
    int blah;
    int j;
    // FILE *fp =  fopen("accessDataTest.txt", "a");   //open file for writing data

    int indices[ITERATIONS];
    int h;


    int q =0;
    while (q < n) {
        // // printf("address of ptr to size %d: %p\n", (1 << (i+2)), (int*)p_int[i] );
        printf("entered the outer loop");
        total_diff = 0;

        for (h = 0; h < ITERATIONS; h++){
            indices[h] = rand() % (1 << (i+3));
        }

        start = rdtsc();

        iter = 0;
        while (iter < ITERATIONS) {

    //         blah = (long)p_int[i][indices[iter]];
    //         iter++;
         }

        end = rdtsc();

        if ((end - start) < THRESHOLD){
            q++;
            total_diff += (end - start);
            printf( "yo: %lf,", total_diff/(double)ITERATIONS);

        }
        else{
            continue;
        }



    }
    printf("\n");
    // free(*p_int);
    // printf("p_int freed\n");
    // fclose(fp);
    // printf("file closed\n");
}









