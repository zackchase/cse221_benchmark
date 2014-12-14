/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd;
     socklen_t clilen;
     int portnum = 12321;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n, m;



    sockfd = socket(AF_INET, SOCK_STREAM, 0);



    printf("closing sockets...");
    close(sockfd);


    return 0;
}
