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

int main(int argc, char **argv) {
    int fd, n;
    int BLKSIZE = 4096; // 4KB
    char *data;

    struct timeval start, end;
    long mtime, secs, usecs;  

    if ( argc != 2 ) {
        printf( "usage: prog, file_to_read");
        return 0;
    }

    // align block and block boundry because of open flag
    posix_memalign((void **) &data, BLKSIZE, BLKSIZE);   
    fd = open(argv[1], O_DIRECT);

    gettimeofday(&start, NULL);
    // printf("Starting of the program, start_t = %ld\n", start);
    while (n = read(fd,data,BLKSIZE)) {
        //printf("Made it into the loop: %d \n", n);
        // printf("%s", data);
    }   
    // int i;
    // for (i=0; i < 10000000000; i++){
    // }
    // end = clock();

    // printf("End of the big loop, end_t = %ld\n", end);
    gettimeofday(&end, NULL);
    
    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs) * 1000000 + usecs) + 0.5;
    printf("%ld\n", mtime/1000);

    close(fd);
}
