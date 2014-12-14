#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

int main(){

    unsigned long long coldstart = 0;
    unsigned long long start = 0;
    unsigned long long end = 0;

    coldstart = rdtsc();
    start = rdtsc();
    end = rdtsc();

    printf("%llu", (end-start));
}

// rdtsc reference
// http://stackoverflow.com/questions/8602336/getting-cpu-cycles-using-rdtsc-why-does-the-value-of-rdtsc-always-increase
