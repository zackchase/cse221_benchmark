
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */



// reference ptheads:
// http://www.amparo.net/ce155/thread-ex.html
// https://computing.llnl.gov/tutorials/pthreads/



/* prototype for thread routine */
void thread1_function ( void *ptr );
void thread2_function ( void *ptr );


static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}


/* struct to hold data to be passed to a thread
   this shows how multiple data items can be passed to a thread */
typedef struct str_thdata
{
    int thread_no;
    int*  tochild;
    int* toparent;
    char* buf;
    char* message;
    int* timer;

} thdata;

int main()
{

    float* time_diff;
    int coldstart = 0;
    int start = 0;
    int end = 0;
    int child_pid = 0;

    int n;
    int tochild[2];
    int toparent[2];
    char buf[2];
    char *to_child_data = "p";
    char *to_parent_data = "c";


    pipe(tochild);
    pipe(toparent);


    pthread_t thread1, thread2;  /* thread variables */
    thdata data1, data2;         /* structs to be passed to threads */

    /* initialize data to pass to thread 1 */
    data1.thread_no = 1;
    data1.tochild = tochild;
    data1.toparent = toparent;
    data1.buf = buf;
    data1.message = to_child_data;
    data1.timer = time_diff;

    data2.thread_no = 2;
    data2.tochild = tochild;
    data2.toparent = toparent;
    data2.buf = buf;
    data2.message = to_parent_data;
    data2.timer = time_diff;



    coldstart = rdtsc();
    start = rdtsc();


    /* create threads 1 and 2 */
    pthread_create(&thread1, NULL, (void *) &thread1_function, (void *) &data1);
    pthread_create(&thread2, NULL, (void *) &thread2_function, (void *) &data2);

    /* Main block now waits for both threads to terminate, before it exits
       If main block exits, both threads exit, even if the threads have not
       finished their work */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    end = rdtsc();
    /* exit */
    exit(0);
} /* main() */

/**
 * print_message_function is used as the start routine for the threads used
 * it accepts a void pointer
**/
void thread1_function ( void *ptr )
{
    thdata *data;
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */

    /* do the work */

    //printf("Thread %d says %s \n", data->thread_no, data->message);

    int start = rdtsc();

    write(data->tochild[1], data->message, strlen(data->message));

    int n = read(data->toparent[0], data->buf, 1);
    /* printf("%s", buf); */
    int end = rdtsc();
    printf("%d", (end-start));


    pthread_exit(0); /* exit */
} /* print_message_function ( void *ptr ) */

void thread2_function( void *ptr ){
    thdata *data;
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */

    /* do the work */
    //printf("Thread %d says %s \n", data->thread_no, data->message);

    int n = read(data->tochild[0], data->buf, 1);
    data->buf[n] = 0; /* terminate the string */
    write(data->toparent[1], data->message, strlen(data->message));

    pthread_exit(0); /* exit */
}