#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>

#define SERV_IP "172.17.98.161"
#define SERV_PORT 6666
#define MAXLINE 8192
#define OPEN_MAX 5000

int main(int argc, int* argv[])
{
    int i, listenfd, connfd, sockfd;
    int n, num = 0;
    ssize_t nready, efd, res;
    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    socklen_t clilen;

    struct sockaddr_in clie_addr, serv_addr;
    struct epoll_event tep, ep[OPEN_MAX];     //tep:epoll_ctl参数  ep[] : epoll_wait参数

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //端口复用

    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    listen(listenfd, 128);
    
    printf("服务器等待连接 ");
    printf("SERV_IP ：%s SERV_PORT %d\n",
            inet_ntop(AF_INET, &serv_addr.sin_addr, str, sizeof(str)),
            ntohs(serv_addr.sin_port));

    efd = epoll_create(OPEN_MAX);             //创建epoll模型，efd指向红黑树根节点
    if (efd == -1){
        perror("epoll_create error!");
        exit(1);
    }
    tep.events = EPOLLIN; tep.data.fd = listenfd; //指定lfd的监听事件为读
    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep); //将lfd及对应的结构体设置到树上，efd可以找到该数（红黑树）
    if(res == -1){
        perror("epoll_ctl erroro");
        exit(1);
    }

    while(1){
        nready = epoll_wait(efd, ep, OPEN_MAX, -1);//-1表示永久阻塞，ep为 struct epoll_event类型数组返回数组，OPEN_MAX为数组容量
        if(nready == -1){
            perror("epoll_wait error");
            exit(1);
        }
        for(i = 0; i < nready; i++)
        {
            if(!(ep[i].events & EPOLLIN)) //如果不是读事件继续循环
                continue;

            if(ep[i].data.fd == listenfd){//如果是请求连接的事件，则服务器接收连接，并将改文件描述符，放进监听队列
                clilen = sizeof(clie_addr);
                connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clilen);

                printf("received from %s at PORT %d\n",
                        inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                        ntohs(clie_addr.sin_port));
                printf("cfd %d----client %d\n", connfd, ++num);
                
                tep.events = EPOLLIN; tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep); //将该事件，放进监听队列
                if(res == -1){
                    perror("epoll_ctl error");
                    exit(1);
                }
            }
            else{                         //如果不是请求连接的，那就是有数据需要读的（有数据需要接收）
                sockfd = ep[i].data.fd;
                n = read(sockfd, buf, MAXLINE);

                if(n == 0) {              //读到零， 说明客户端关闭连接
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);

                    if(res == -1) {
                        perror("epoll_ctl error");
                        exit(1);
                    }
                    close(sockfd);
                    printf("client[%d] closed connection\n", sockfd);
                } else if(n < 0){         //小于零则说明读数据出错
                    perror("read n < 0 error");
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
                    close(sockfd);
                } else {                  //读到实际数据的字节数
                    for(i = 0;i < n; i++)
                        buf[i] = toupper(buf[i]);  //做大写转换

                    write(STDOUT_FILENO, buf, n);  //写出到服务器端的页面
                    write(sockfd, buf, n);         //写回给客户端
                }

            }
        }
    }
    close(listenfd);   //关闭服务器连接文件描述符
    close(efd);        //关闭监听队列（平衡二叉树节点，红黑树）
    return 0;
}
