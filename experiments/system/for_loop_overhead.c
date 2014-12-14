#include<sys/time.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

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
    unsigned long long i = 0;

    coldstart = rdtsc();
    start = rdtsc();
    
    // uncomment for loop header for entering for loop overhead
    // other header used to measure each iteration cost
    for (i=0;i<1000;i++) {
    // for (i=0;i<1;i++) {
    }
    end = rdtsc();

    printf("%llu", (end-start));
}
