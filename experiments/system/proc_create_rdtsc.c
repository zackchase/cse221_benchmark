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

    unsigned long long start,end;
    // int end = 0;
    int child_pid = 0;

    // struct timeval start, end;
    // long secs, usecs;
    // float mtime;

    // fart = rdtsc();

    start = rdtsc();
    // gettimeofday(&start, NULL);

    child_pid = fork();


    

    if (child_pid > 0 ){
        // gettimeofday(&end, NULL);
        end = rdtsc();
        printf("killing child\n");
        kill(child_pid,SIGKILL);
    }

    // secs  = end.tv_sec  - start.tv_sec;
    // usecs = end.tv_usec - start.tv_usec;
    // mtime = ((secs) * 1000000 + usecs) + 0.5;
    // printf("%f\n", mtime/1000);

    printf("start: %llu\n", start);
    printf("end: %llu\n", end);

    printf("diff: %llu\n", (end-start));


}
