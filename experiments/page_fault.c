#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>


#define ITERATIONS 10000
#define THRESHOLD 100000000000

#define EXPONENT1 29
#define EXPONENT2 32

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
    long i;
    long unit = 1;

    printf("Allocating first array. \n");

    // Allocate one giant array (size of RAM) = 2^32 ints
    int* arr1 = (int*)malloc(sizeof(int) * (unit << EXPONENT2));
    for (i=0; i<(unit << EXPONENT2); i++){
        arr1[i]= i;
    }

    int* indices = (int*)malloc(sizeof(long) * ITERATIONS);

    int h;
    for (h=0; h< ITERATIONS; h++){
        indices[h] = random() % (unit<< EXPONENT2);
    }


    printf("Completed indices array. Everything should be paged out.\n");


    fart = rdtsc();

    start = rdtsc();

    i = arr1[147890002];

    end = rdtsc();




    diff = end - start;
    printf("%llu", diff);

    free(arr1);


}
