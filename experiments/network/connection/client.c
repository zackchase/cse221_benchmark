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
    char write_buffer[256] = "hello";

    int portnum = 12321;
    unsigned int start_time, end_time;

    //// uncomment for set up
    // start_time = rdtsc();
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
        bzero(read_buffer, 256);
        n = write(sockfd,write_buffer,strlen(write_buffer));
        m = read(sockfd,read_buffer,255);
    //// uncomment for setup
    // end_time = rdtsc();

    if (m < 0) {
        error("ERROR reading from socket");
    }
    // printf("%s\n", read_buffer);
    // printf("round trip time: %d\n", (end_time-start_time));

    bzero(read_buffer,256);
    //bzero(write_buffer, 256);
    //fgets(write_buffer,255,stdin);
    
    //// uncomment for teardown
    // start_time = rdtsc();
    close(sockfd);
    //// uncomment for teardown
    // end_time = rdtsc();
    printf("%d\n", end_time - start_time);

    return 0;
}
