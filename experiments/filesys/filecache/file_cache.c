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
    if ( argc != 3 ) {
        printf( "ERROR. usage: prog, filename, filesize (bytes)\n");
        return 0;
    }
    int fd, n, i;
    int BLKSIZE = 4096; // 4KB
    char *data;

    // rdtsc doesn't work here because values wrapping after cast
    struct timeval start, end;
    long mtime, secs, usecs;
    int numblocks = atoi(argv[2])/(BLKSIZE);
    int offset[10000];

    srand(time(NULL));

    for (i = 0; i < 10000; i++) {
        offset[i] = rand() % numblocks;
    }

    posix_memalign((void **) &data, BLKSIZE, BLKSIZE);

    fd = open(argv[1], O_RDONLY);
    // printf("First reading the whole file in sequentially\n");
    while (n = read(fd,data,BLKSIZE)) {
        //printf("Made it into the loop: %d \n", n);
        // printf("%s", data);
    }

    // printf("Then reading in 10000 blocks randomly\n");
    gettimeofday(&start, NULL);
        for (i = 0; i < 10000; i++) {
            n = pread(fd,data,BLKSIZE,offset[i]*BLKSIZE);
            if (n < 0) {
                printf("fail\n");
            }
        }
    gettimeofday(&end, NULL);

    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs) * 1000000 + usecs) + 0.5;
    printf("%ld\n", mtime/1000);

    close(fd);
}
