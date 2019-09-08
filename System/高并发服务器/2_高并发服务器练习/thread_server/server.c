#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>

#define MAXLINE 8192
#define SERV_IP "172.17.98.161"
#define SERV_PORT 8880

struct s_info{
  struct sockaddr_in cliaddr;
  int cfd;
};

void *do_work(void *arg)
{
  int n, i;
  struct s_info *ts = (struct s_info*)arg;//获取传过来的参数强转为 自定义类型
  char buf[MAXLINE];
  char str[INET_ADDRSTRLEN];

  while(1){
    n = read(ts->cfd, buf, MAXLINE);//从客户端读取数据
    if(n == 0)//读到0说明客户端退出连接
    {
      printf("the client %d closed...\n",ts->cfd);
      break;//跳出循环关闭文件描述符
    }
    printf("received from  %s at PORT %d",
        inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str)),
        ntohs((*ts).cliaddr.sin_port));

    for(i = 0; i < n; i++)
    {
      buf[i] = toupper(buf[i]);
    }
    write(ts->cfd, buf, n);
    write(STDOUT_FILENO, buf, n);
  }

  close(ts->cfd);//关闭连接
  return (void *) 0;
}

int main(void)
{
  struct sockaddr_in servaddr, cliaddr;
  socklen_t cliaddr_len;
  int listenfd, connfd;
  pthread_t tid;
  struct s_info ts[256];//根据最大线程数，创建结构体数组
  int i= 0;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr.s_addr);

  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  listen(listenfd, 128);

  printf("Accepting client connect ...\n");

  while(1)
  {
    cliaddr_len = sizeof(cliaddr);
    connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &cliaddr_len);
    ts[i].cfd = connfd;
    ts[i].cliaddr = cliaddr;

    /*达到线程最大数时，pthread_create出错处理，增加服务器稳定性*/

    pthread_create(&tid, NULL, do_work, (void *)&ts[i]);
    pthread_detach(tid);
    i++;
  }
  return 0;
}


