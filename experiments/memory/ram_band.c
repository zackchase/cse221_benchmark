
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

static __inline__ unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}


int main() {

    unsigned long long start = 0;
    unsigned long long  end = 0;
    unsigned long long fart = 0;
    int j;
    unsigned long long diff = 0;
    int i;

    int* arr = (int*)malloc(sizeof(int) * (1 << EXPONENT));

    fart = rdtsc();

    start = rdtsc();
    for (i=0; i<(1<<EXPONENT); i++){
        arr[i] = 12345;
    }
    end = rdtsc();

    diff = end - start;
    printf("%llu\n", diff);

    free(arr);
}
