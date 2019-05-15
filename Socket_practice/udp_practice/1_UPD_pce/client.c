#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define SERV_PORT 6666

int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    int sockfd, n;
    char buf[BUFSIZ];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "172.17.98.161", &serv_addr.sin_addr);

    while(fgets(buf, BUFSIZ, stdin) != NULL)
    {
        n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if(n == -1)
            perror("sendto error!");

        n = recvfrom(sockfd, buf, BUFSIZ, 0, NULL, 0);
        if(n == -1)
            perror("received error!");

        write(STDOUT_FILENO, buf, n);
    }
    close(sockfd);
    return 0;
}
