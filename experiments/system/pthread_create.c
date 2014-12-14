#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>


static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}


/* this function is run by the second thread */
void *inc_x(void *x_void_ptr)
{

/* increment x to 100 */
int *x_ptr = (int *)x_void_ptr;
while(++(*x_ptr) < 100);

//printf("x increment finished\n");

/* the function must return something - NULL will do */
return NULL;

}


int main(){

    float avg_diff;
    unsigned long long coldstart = 0;
    unsigned long long start = 0;
    unsigned long long end = 0;
    // struct timeval start, end;
    // long secs, usecs;
    // float mtime;


    int child_pid = 0;
    int x = 0, y = 0;

    pthread_t inc_x_thread;



    coldstart = rdtsc();

    start = rdtsc();
    //gettimeofday(&start, NULL);
    if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;

    }

    // gettimeofday(&end, NULL);
    end = rdtsc();


    // secs  = end.tv_sec  - start.tv_sec;
    // usecs = end.tv_usec - start.tv_usec;
    // mtime = ((secs) * 1000000 + usecs) + 0.5;
    // printf("%f\n", mtime/1000);


    printf("%llu", (end-start));


}
