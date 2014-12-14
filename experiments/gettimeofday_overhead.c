#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>





int main(){



    struct timeval start, end;
    long secs, usecs;
    float mtime;

    int a;

    gettimeofday(&start, NULL);

    a = getpid();

    gettimeofday(&end, NULL);

    //printf("%d", (end-start));
    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs) * 1000000 + usecs) + 0.5;
    printf("%f\n", mtime/1000);


}
