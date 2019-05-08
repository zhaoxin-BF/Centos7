#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>
#include <sys/wait.h>

//脑残命令访问 nc 172.17.98.161 8888

void wait_child(int signo)               //回收僵尸进程
{
    while(waitpid(0, NULL, WNOHANG) > 0);
    return;
}

#define SERV_IP "172.17.98.161"
#define SERV_PORT 8888

int main()
{
    int lfd, cfd;
    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len;
    char buf[BUFSIZ],clie_IP[BUFSIZ];
    int n,i;

    lfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);              //初始化IP01
    //inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr); //初始化IP02

    bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    listen(lfd, 128);      //允许有多少个客户端跟我进行三次握手，最大为128
    printf("服务器启动完毕，等待客户端连接............\n"); 
    pid_t pid;
    while(1){
        clie_addr_len = sizeof(clie_addr);
        cfd = accept(lfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
        //打印客户端 IP地址 和 端口号
        printf("client IP:%s, port:%d\n",
                inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr,
                clie_IP,sizeof(clie_IP)),
                ntohs(clie_addr.sin_port));
        pid = fork();
        if(pid < 0)
        {
            perror("fork error!");
            return 0;
        }
        else if (pid == 0)   //pid 等于 0 说明是子进程
        {
            close(lfd);
            break;
        }//不需要接收客户端了，所以关闭lfd;
        else
        {
            close(cfd);
            signal(SIGCHLD, wait_child);
        }
    }
    if(pid == 0)
    {
        while(1)
        {
            n = read(cfd,buf, sizeof(buf));
            if(n == 0) //client close
            {
                close(cfd);
                return 0;   //or  exit(1)
            } 
            else if(n == -1)
            {
                perror("read error!");
                return 0;
            } 
            else
            {
                for(i = 0; i < n; i++)
                {
                    buf[i] = toupper(buf[i]);
                }
                write(cfd, buf, n);           //写回给客户端
                write(STDOUT_FILENO, buf, n); //打印至屏幕
            }
        }
    }
    return 0;
}








