#define _GNU_SOURCE 
#define CPMS 1000000.0
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <errno.h>
#include <time.h>

int main(int argc, char **argv)
{
    int fd, n;
    int BLKSIZE = 4096;
    char *data;
    // clock_t start, end;
    // double total;

    struct timeval start, end;
    long mtime, secs, usecs;  

    // char *file = "foo.txt";
    // char *file = "foo15mb.txt";
    // char *file = "foo31mb.txt";
    // char *file = "foo62mb.txt";
    // char *file = "foo125mb.txt";
    // char *file = "foo250mb.txt";
    // char *file = "foo500mb.txt";
    // char *file = "foo1gb.txt";

    if ( argc != 2 ) {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename", argv[0] );
        return 0;
    }
    // char *file = ;

    posix_memalign((void **) &data, BLKSIZE, BLKSIZE);
   
    fd = open(argv[1], O_DIRECT);

    // start = clock();
    gettimeofday(&start, NULL);
    // printf("Starting of the program, start_t = %ld\n", start);

    while (n=read(fd,data,BLKSIZE)) {
        //printf("Made it into the loop: %d \n", n);
        // printf("%s", data);
    }   
    // int i;
    // for (i=0; i < 10000000000; i++){
    // }
    // end = clock();

    // printf("End of the big loop, end_t = %ld\n", end);
                                    
    // total = (double)(end - start)/(double)CLOCKS_PER_SEC;

    // printf("Total time taken by CPU: %f\n", total);

    gettimeofday(&end, NULL);
    

    // printf("file time: %f\n", (end-start));
    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs) * 1000000 + usecs) + 0.5;
    printf("%ld\n", mtime/1000);

    close(fd);
}
