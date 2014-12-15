#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#define OFFSET_LENGTH 10000

int main(int argc, char **argv) {

    if ( argc != 2 ) {
        printf( "error: prog, num processes" );
        return 0;
    }
    int PROCESSES = atoi(argv[1]);
    int i,j,k,n,fd,f;
    int children[PROCESSES];
    int offset[OFFSET_LENGTH];

    srand(time(NULL));
    struct timeval start, end;
    long mtime, secs, usecs;

    int BLKSIZE = 4096;
    char *data;

    int child;

    char file_addr[16];
    posix_memalign((void **) &data, BLKSIZE, BLKSIZE);

    for (k = 0; k < OFFSET_LENGTH; k++) {
        offset[k] = rand() % 100;
    }
    //printf("done generate randoms\n");

    for (i = 0; i < PROCESSES; i++) {
        child = fork();
        children[i] = child;
        //printf("yo");
        if (child != 0) {
            //printf("child %d created with pid %d\n", i, child);
            continue;
        }
        else {
            break;
        }
    }

    //printf("made it out of process creation loop\n");
    //printf("my child is: %d\n", child);

    if (child == 0) {
        sprintf(file_addr, "foo%d.txt", i);
        //printf("child file name assigned successfully");
        f = open(file_addr, O_DIRECT);
        //printf("child file opened \n");

        while (1){
             for (j = 0; j < OFFSET_LENGTH; j++){
                 n = pread(f,data,BLKSIZE,offset[j]*BLKSIZE);
            }
            //printf("made it through some child reading\n");
        }
    }

    else {
        fd = open("foo.txt", O_DIRECT);
        //printf("in parent\n");
        gettimeofday(&start, NULL);
            for (j = 0; j < OFFSET_LENGTH; j++){
                n = pread(fd,data,BLKSIZE,offset[j]*BLKSIZE);
            }
        gettimeofday(&end, NULL);

        // Kill Children
        for (i = 0; i < PROCESSES; i++){
            kill(children[i], SIGKILL);
            //printf("killed proc %d\n", children[i]);
        }

        secs  = end.tv_sec  - start.tv_sec;
        usecs = end.tv_usec - start.tv_usec;
        mtime = ((secs) * 1000000 + usecs) + 0.5;
        printf("%ld", mtime/1000);
    }
}