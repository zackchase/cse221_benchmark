#include <time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define ITERATIONS 100000000
#define THRESHOLD 100000000000

static __inline__ unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

int*** make_array(int exponent){
    int*** arr = malloc((1 << exponent) * sizeof(int*));
    int i;
    for (i = 0; i < (1 << exponent); i++) {
        if (i == ((1 << exponent) - 1)) {
            arr[i] = (int **)&arr[0];
        }
        else {
            arr[i] = (int **)&arr[i+1];
        }
        // printf("value at arr[%d]: %d at addr %p\n", i, arr[i], &arr[i]);
    }
    return arr;
}


int main() {

    int*** q = make_array(2);
    // printf("address of head: %u\n", q );
    // printf("value in q[0]: %u\n", q[0]);
    // printf("address of q[1]: %u\n", &q[1] );

    // printf("value in q[1]: %u\n", q[1]);
    // printf("value in q[2]: %u\n", q[2]);
    // printf("value in q[3]: %u\n", q[3]);

    free(q);

    unsigned long total_diff = 0;
    unsigned long start = 0;
    unsigned long end = 0;
    int j;
    int **p;
    unsigned long diff = 0;
    int*** head;
    int i = 1;

    while (i <= 28){
        total_diff = 0;

        head = make_array(i);
        p = (int **) head;
        j = 0;

        start = rdtsc();
        while ( j< ITERATIONS){
               // printf("address of p: %p\n", p );
               // printf("value contained in p: %p\n",*p );
            p =  (int**)*p;
               // printf("address of p: %p\n", p );
               // printf("value contained in p: %p\n",*p );
            j++;
            total_diff += diff;
        }
        end = rdtsc();

        diff = end-start;
        free(head);

        if (diff < THRESHOLD){
            i++;
            // printf("exponent size for array: %d\n", i);
            printf("%lu\n", diff);
        }
        else {
            continue;
        }
    }
}
