#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

#define SERV_IP "172.17.98.161"
#define SERV_PORT 6666

int main(int argc, char *argv[])
{
    int i, j, n, maxi;
    int nready, client[FD_SETSIZE];
    int maxfd, listenfd, connfd, sockfd;      //自定义数组client, 防止遍历1024个文件描述符 FD_SETSIZE默认为1024
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];   //#define INET_ADDRSTRLEN 16

    struct sockaddr_in clie_addr, serv_addr;
    socklen_t clie_addr_len;
    fd_set rset, allset;                      //rset 读事件文件描述符集合 allset 用来暂存

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 20);

    maxfd = listenfd;                         //起初 listenfd 为最大的文件描述符 = 3
    maxi = -1;
    for(i = 0;i<1024;i++)
    {
        client[i] = -1;
    }

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    while(1)
    {
        rset = allset;                        
        nready  = select(maxfd+1, &rset, NULL, NULL, NULL);               //循环询问代理，是否有符合响应
        if(nready < 0)
        {
            perror("select error");
        }
        if(FD_ISSET(listenfd, &rset))                                     //如果有需要请求连接的客户端，服务器执行连接操作
        {
            clie_addr_len = sizeof(clie_addr);
            connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
            printf("received from %s at PORT %d\n",
                    inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                    ntohs(clie_addr.sin_port));
            for(i = 0; i< FD_SETSIZE; i++)                                //将客户端连接的文件描述符，存入已监听的数组中
            {
                if(client[i] < 0)
                {
                    client[i] = connfd;
                    break;
                }
            }
            if(i == FD_SETSIZE)                                           //如果数组超员，输出太多客户端连接
            {
                fputs("too many clients\n",stderr);
                exit(1);
            }

            FD_SET(connfd, &allset);                                      //将该文件描述符，存入select监听队列
            if(connfd > maxfd)                                            //修改select，最大监听文件描述符
            {
                maxfd = connfd;
            }
            if(i>maxi)                                                    //修改自定义已监听数组最大下标
            {
                maxi = i;
            }
            if(--nready == 0)             //如果select 返回的需要处理的事件个数已经全部处理完毕，则继续循环问select。
                continue;
        }

        for(i = 0; i <= maxi; i++)        //如果select的nready事件没有处理完毕，则继续循环从已监听的数组client中取文件描述符，
        {                                 //看其是否在rest中
            if((sockfd = client[i]) < 0)  
                continue;
            if(FD_ISSET(sockfd, &rset))   //如果sockfd 在rset中。
            {
                if((n =read(sockfd, buf, sizeof(buf))) == 0)   //读取sockfd 发送过来的数据为0，则表示没有数据，不需要处理
                { 
                    close(sockfd);                             //关闭这个文件描述符
                    FD_CLR(sockfd, &allset);                   //将其从所有监听的文件描述符中去掉
                    client[i] = -1;                            //将其从已监听的文件描述符中去掉
                }
                else if( n > 0)                                //如果从其中读取到了数据，则执行小写转大写操作
                {
                    for(j = 0; j< n; j++)
                    {
                        buf[j]=toupper(buf[j]);
                    }
                    write(sockfd, buf, n);                     //写回给客户端
                }
                if(--nready == 0)                           //需要执行的事件为0，则继续循环向select ，询问需要处理的文件操作
                {
                    break;                                  //跳出当前循环
                }
            }
        }
    }
    close(listenfd);
    return 0;
}











