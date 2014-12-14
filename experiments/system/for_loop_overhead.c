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

    int fart = 0;
    int start = 0;
    int end = 0;
    int i = 0;

    fart = rdtsc();
    start = rdtsc();
    for (i=0;i<1000;i++) {
    }
    end = rdtsc();

    printf("%d", (end-start));
}
