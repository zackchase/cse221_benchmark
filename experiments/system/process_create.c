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

    // struct timeval start, end;
    // long secs, usecs;
    // float mtime;

    coldstart = rdtsc();

    start = rdtsc();
    //gettimeofday(&start, NULL);

    child_pid = fork();


    end = rdtsc();

    if (child_pid > 0 ){
        //gettimeofday(&end, NULL);
        kill(child_pid,SIGKILL);
    }

    // secs  = end.tv_sec  - start.tv_sec;
    // usecs = end.tv_usec - start.tv_usec;
    // mtime = ((secs) * 1000000 + usecs) + 0.5;
    // printf("%f\n", mtime/1000);

    printf("%llu", (end-start));


}
