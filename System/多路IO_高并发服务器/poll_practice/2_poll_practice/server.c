#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>
#include <ctype.h>

#define MAXLINE 80
#define SERV_PORT 8888
#define OPEN_MAX 1024

int main(int argc, char *argv[])
{
    int i, j, maxi, listenfd, connfd, sockfd;
    int nready;          //接收poll返回值，记录满足监听事件的fd个数

    ssize_t n;

    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    socklen_t clie_len;
    struct pollfd client[OPEN_MAX];
    struct sockaddr_in clie_addr, serv_addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 128);

    client[0].fd = listenfd;
    client[0].events = POLLIN;

    for(i = 1; i < OPEN_MAX; i++)
        client[i].fd = -1;

    maxi = 0;

    while(1)
    {
        nready = poll(client, maxi+1, -1);

        if(client[0].revents & POLLIN){
            clie_len = sizeof(clie_addr);
            connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_len);
            printf("received from %s at PORT %d\n",
                    inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                    ntohs(clie_addr.sin_port));

            for (i = 1; i < OPEN_MAX; i++)
                if(client[i].fd < 0){           //在这个bug 上耗费了快四个小时
                    client[i].fd = connfd;      //client[i].fd < 0, 是小于0。。。。。
                    break;                      //醉了醉了醉了，不过好在是解决了
                }                               //留个日期纪念下2019_5_12
            client[i].events = POLLIN;
            if(i > maxi)
                maxi = i;
            if(--nready <= 0)
                continue;
        }

        for (i = 1; i<= maxi; i++){
            if((sockfd = client[i].fd) < 0)
                continue;

            if(client[i].revents & POLLIN){
                if((n = read(sockfd, buf, MAXLINE)) < 0) {
                    if(errno == ECONNRESET) {
                        printf("client[%d] aborted connection\n", i);
                        close(sockfd);
                        client[i].fd = -1;
                    } else
                    {
                        perror("read error");
                        exit(1);
                    }
                } else if(n == 0)
                {
                    printf("client[%d] closed connection\n", i);
                    close(sockfd);
                    client[i].fd = -1;
                } else {
                    for(j = 0; j<n; j++)
                        buf[j] = toupper(buf[j]);
                    write(sockfd, buf, n);
                }
                if(--nready <= 0)
                    break;
            }
        }
    }
    return 0;
}
