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


// second thread runs this dummy increment function
void *inc_x(void *x_void_ptr) {
    int *x_ptr = (int *)x_void_ptr;
    while(++(*x_ptr) < 100);

    //printf("x increment finished\n");
    return NULL;
}


int main(){

    unsigned long long coldstart = 0;
    unsigned long long start = 0;
    unsigned long long end = 0;
    
    int child_pid = 0;
    int x = 0, y = 0;

    pthread_t inc_x_thread;
    coldstart = rdtsc();

    start = rdtsc();
    if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    end = rdtsc();

    printf("%llu", (end-start));
}
