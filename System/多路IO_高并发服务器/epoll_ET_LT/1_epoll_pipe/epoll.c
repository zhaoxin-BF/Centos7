#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>

#define MAXLINE 10

int main(int argc, char *argv[])
{
    int efd, i;
    int pfd[2];//1
    pid_t pid;      
    char buf[MAXLINE], ch = 'a';

    pipe(pfd);//2
    pid = fork(); //创建子进程

    if (pid == 0) {             //子 写
        close(pfd[0]);          //关闭读端，随机关闭。父进程相反就好了
        while (1) {
            //aaaa\n
            for (i = 0; i < MAXLINE/2; i++)
                buf[i] = ch;
            buf[i-1] = '\n';
            ch++;
            //bbbb\n
            for (; i < MAXLINE; i++)
                buf[i] = ch;
            buf[i-1] = '\n';
            ch++; //ch++ 就变成b了
            //aaaa\nbbbb\n
            write(pfd[1], buf, sizeof(buf));
            sleep(5);
        }
        close(pfd[1]);                          //写完之后关闭写端

    } else if (pid > 0) {       //父 读
        struct epoll_event event;
        struct epoll_event resevent[10];        //epoll_wait就绪返回event
        int res, len;

        close(pfd[1]);
        efd = epoll_create(10);                 //创建epoll红黑树根节点

        event.events = EPOLLIN | EPOLLET;        // ET 边沿触发 _没读完第二次就不触发了。
                                                 //所以可能就会有bug.
        //event.events = EPOLLIN;                // LT 水平触发 (默认)
        event.data.fd = pfd[0];
        epoll_ctl(efd, EPOLL_CTL_ADD, pfd[0], &event); //加入epoll监听队列

        while (1) {
            res = epoll_wait(efd, resevent, 10, -1);   //阻塞等待，管道里面有数据了，就满足了阻塞打开条件
            printf("res %d\n", res);
            if (resevent[0].data.fd == pfd[0]) {
                len = read(pfd[0], buf, MAXLINE/2);
                write(STDOUT_FILENO, buf, len);
            }
        }

        close(pfd[0]);
        close(efd);

    } else {
        perror("fork");
        exit(-1);
    }

    return 0;
}

