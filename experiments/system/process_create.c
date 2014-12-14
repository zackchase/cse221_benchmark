#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

int main(){

    float avg_diff;
    unsigned long long coldstart = 0;
    unsigned long long start = 0;
    unsigned long long end = 0;
    int child_pid = 0;

    coldstart = rdtsc();
    
    start = rdtsc();
        child_pid = fork();
    end = rdtsc();

    if (child_pid > 0 ){
        kill(child_pid,SIGKILL);
    }

    printf("%llu", (end-start));
}
