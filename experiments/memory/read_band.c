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
    int i;
    int sum = 0;

    // allocate some array. doesn't matter if empty
    int* arr = (int*)malloc(sizeof(int) * (1 << EXPONENT));

    coldstart = rdtsc();

    start = rdtsc();
    // walk through the entire array, read value
    for (i = 0; i < (1<<EXPONENT); i++){
        sum += arr[i];
    
    // with loop unrolling
    // for (i = 0; i < (1<<EXPONENT); i+=10){
    //     sum += (arr[i] + arr[i+1] + arr[i+3] +
                // arr[i+4] + arr[i+5] + arr[i+6] +
                // arr[i+7] + arr[i+8] + arr[i+9]);
    }
    end = rdtsc();
    printf("%llu\n", (end - start);

    free(arr);
}
