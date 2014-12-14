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

    unsigned long long fart = 0;
    unsigned long long start = 0;
    unsigned long long end = 0;
    long long diff;
    int i = 0;

    fart = rdtsc();
    start = rdtsc();
    sleep(2);
    end = rdtsc();

    diff = end-start;
    printf("%lld", diff);
}
