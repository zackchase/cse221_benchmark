#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


static __inline__ unsigned long long rdtsc(void)
{
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

// test pipes and stuff
int main(int argc, char **argv) {

    float avg_diff;
    unsigned long long coldstart = 0;
    unsigned long long start = 0;
    unsigned long long end = 0;
    int child_pid = 0;

    int n;
    int tochild[2];
    int toparent[2];
    char buf[1025];
    char *to_child_data = "hello son";
    char *to_parent_data = "hello dad";

    pipe(tochild);
    pipe(toparent);

    child_pid = fork();

    if (child_pid != 0){
        start = rdtsc();
        write(tochild[1], to_child_data, strlen(to_child_data));

    }

    if (child_pid ==0){
        n = read(tochild[0], buf, 1024);
        buf[n] = 0; /* terminate the string */

        write(toparent[1], to_parent_data, strlen(to_parent_data));
    }

    if (child_pid != 0){
        n = read(toparent[0], buf, 1024);
        end = rdtsc();
        printf("%d", (end-start));

    }


    //printf("read %d bytes from the pipe: \"%s\"\n", n, buf);


    //printf("%d", (end-start));

    return 0;


}
