#include <time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>


#define ITERATIONS 100000000
#define THRESHOLD 100000000000

#define EXPONENT 22

static __inline__ unsigned long long int rdtsc(void) {
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

int main() {

    unsigned long long coldstart = 0;
    unsigned long long end = 0;
    unsigned long long start = 0;
    int i, sum;

    // allocate some array. doesn't matter if empty
    int* arr = (int*)malloc(sizeof(int) * (1 << EXPONENT));

    coldstart = rdtsc();

    start = rdtsc();
    // walk through the entire array
    for (i = 0; i < (1<<EXPONENT); i++){
        // dead code
        arr[i] = 12345;
        // non dead code if compiler opts?
        // sum += arr[i];
    }
    end = rdtsc();
    printf("%llu\n", (end - start);

    free(arr);
}
