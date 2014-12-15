#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <time.h>

#define ITERATIONS 1

static __inline__ unsigned long long rdtsc(void) {
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, sock_ret, n, m;
    int filefd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    struct stat file_buf;
    off_t offset = 0;
    char read_buffer[256];
    char write_buffer[256];
    char filename[] = "send.txt";

    int portnum = 12321;
    unsigned long long start_time, end_time;

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
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portnum);
    
    sock_ret = connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
    if ( sock_ret < 0) {
        error("ERROR connecting");
    } else {
        filefd = open(filename, O_RDONLY);
        fstat(filefd, &file_buf);
        offset = 0;

        start_time = rdtsc();
        n = sendfile(sockfd, filefd, &offset, file_buf.st_size);
        if (n < 0) {
            error("ERROR sending file");
        }
        if (n == file_buf.st_size) {
            end_time = rdtsc(); 
            close(sockfd);
        }
        // m = read(sockfd,read_buffer,255);        
        // if (m < 0) {
        //     error("ERROR reading from socket");
        // }
        // printf("%s\n", read_buffer);
        printf("time: %lu\n", (end_time-start_time));
    }
    close(sockfd);
    close(filefd);
    return 0;
}
