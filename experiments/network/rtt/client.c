#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define ITERATIONS 1000

static __inline__ unsigned long long rdtsc(void) {
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, n, m;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char read_buffer[256];
    char write_buffer[256];

    int portnum = 12321;
    unsigned long long start, end;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portnum);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(write_buffer,256);
    fgets(write_buffer,255,stdin);

    bzero(read_buffer, 256);
    int i;
    unsigned long long total_time = 0;

    for (i = 0; i<ITERATIONS; i++) {
        start = rdtsc();
        n = write(sockfd,write_buffer,strlen(write_buffer));
        m = read(sockfd,read_buffer,255);
        end = rdtsc();

        if (m < 0) {
            error("ERROR reading from socket");
        }
        // printf("%s\n", read_buffer);
        if (end - start < 25000000 && end - start > 7000000) {
            total += end - start;
        }
        else {
            i--;
        }
        bzero(read_buffer,256);
    }

    double avg_time = (double) total / (double) ITERATIONS;
    printf("avg time: %lf \n", avg_time);
    close(sockfd);
    return 0;
}