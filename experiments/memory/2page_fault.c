#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

static __inline__ unsigned long long int rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

int main(){

    unsigned long long fstart, start, end;


    int descriptor = open("testfile", O_RDONLY);
    int page_size = getpagesize();
    char* data;
    char p = ' ';

    fstart = rdtsc();
    start = rdtsc();

    data = mmap((caddr_t)0, page_size, PROT_READ, MAP_SHARED, descriptor,
    10* page_size);
    p = data[2];

    end = rdtsc();


    printf("%llu", end-start);
    //printf("Reading in a page of size %d took %llu cycles \n", page_size, end-start);
    //printf("content of data: %c%c%c%c", data[0], data[1], data[2], data[3]);
    return 0;

}
