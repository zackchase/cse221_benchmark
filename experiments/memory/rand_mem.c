#include <time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define ITERATIONS 1000000
#define THRESHOLD 10000000000000

static __inline__ unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

int* make_array(int exponent){
    // make arrays filled with random values
    int* arr = malloc((1 << exponent) * sizeof(int));
    int i;
    for (i = 0; i < (1 << exponent); i++) {
        arr[i] = rand() % (1 << exponent);
    }
    return arr;
}


int main() {

    // int* q = make_array(2);
    // // printf("address of head: %u\n", q );
    // // printf("value in q[0]: %u\n", q[0]);
    // // printf("address of q[1]: %u\n", &q[1] );

    // // printf("value in q[1]: %u\n", q[1]);
    // // printf("value in q[2]: %u\n", q[2]);
    // // printf("value in q[3]: %u\n", q[3]);

    // free(q);

    unsigned long total_diff = 0;
    unsigned long start = 0;
    unsigned long end = 0;
    int j, p;
    unsigned long diff = 0;
    int* head;
    int i = 1;
    int* indices = (int*)malloc(sizeof(int) * ITERATIONS);

    srand(time(NULL));
    while (i <= 30){
        total_diff = 0;
        head = make_array(i);
        int h;
        
        // for each array size, make a different random index array to help access later
        for (h = 0; h < ITERATIONS; h++){
            indices[h] = rand() % (1<<i);
        }
        
        j = 0;
        // do iterations of random array access
        // if time is constant to access random, proabably in sitting in cache
        // if it takes longer, it might be in L2 or L3 cache
        start = rdtsc();
        while (j < ITERATIONS){
            //printf("entered the loop!  ");
            p = head[indices[j]];
            j++;
        }
        end = rdtsc();

        total_diff = end-start;
        free(head);

        if (total_diff < THRESHOLD){
            // printf("exponent size for array: %d\n", i);
            //printf("Exp: %d, Avg latency %lf\n", i, (double)total_diff/ITERATIONS);
            printf("%lf\n", (double)total_diff/ITERATIONS);
            i++;
        }
        else {
            continue;
        }
    }
}