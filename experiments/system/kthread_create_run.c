#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/kthread.h>


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
    int child_pid = 0;

    int *data = malloc(sizeof(int)*5);


    fart = rdtsc();
    start = rdtsc();

    struct task_struct *__k = kthread_create(thread_fn, *data);
    if (!IS_ERR(__k))     {
        wake_up_process(__k);
    }


    end = rdtsc();

    if (child_pid > 0 ){
    }

    kthread_stop(task_struct)

    printf("%d", (end-start));


}

int thread_fn(){
    return;
};
