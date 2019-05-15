#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>

#define SERVER_PORT 8000
#define MAXLINE 1500

#define BOARDCAST_IP "172.17.111.255"
#define CLIENT_PORT 9000

int main()
{
    int sockfd;
    struct sockaddr_in serv_addr, clie_addr;
    char buf[MAXLINE];

    //构造UDP通信的套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int flag = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));

    //构造client IP地址 + 端口 172.17.98.161 + 9000
    bzero(&clie_addr, sizeof(clie_addr));
    clie_addr.sin_family = AF_INET;
    inet_pton(AF_INET, BOARDCAST_IP, &clie_addr.sin_addr.s_addr);
    clie_addr.sin_port = htons(CLIENT_PORT);

    int i = 0;

    while(1)
    {
        sprintf(buf, "Drink %d glass of water\n", i++);

        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&clie_addr, sizeof(clie_addr));
        sleep(1);
    }
    close(sockfd);
    return 0;
}
