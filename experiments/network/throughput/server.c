#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd;
    socklen_t clilen;
    int portnum = 12321;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int sock_ret, n, m;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portnum);

    sock_ret = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if ( sock_ret < 0) {
        error("ERROR on binding");
    }
              
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
    if (newsockfd < 0) {
        error("ERROR on accept");
    }
    do {
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) {
            error("ERROR reading from socket");
        }
        // printf("%s\n", buffer);
    } while (n != 0);
    // m = write(newsockfd,"fuck this",8);
    // printf("%s", buffer);
    printf("closing sockets...\n");
    close(newsockfd);
    close(sockfd);
    return 0;
}