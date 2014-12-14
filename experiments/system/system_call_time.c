#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}




int main(){

    float avg_diff;
    int fart = 0;
    int start = 0;
    int end = 0;
    int pid = 0;

    fart = rdtsc();
    start = rdtsc();
        pid = getpid();
    end = rdtsc();





    printf("%d", (end-start));


}
