#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>
#include <sys/wait.h>

#define SERV_PORT 8888


void wait_child(int signo)
{
  while(waitpid(0, NULL, WNOHANG) > 0);
  return;
}

int main()
{
  int lfd,cfd;
  struct sockaddr_in serv_addr, clie_addr;
  char buf[BUFSIZ], clie_IP[BUFSIZ];
  socklen_t clie_addr_len;
  int n , i;

  lfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port  = htons(SERV_PORT);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  //inet_pton(AF_INET, "172.17.98.161", &serv_addr.sin_addr.s.addr);

  bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

  listen(lfd, 128);

  printf("服务器启动完毕!,等待客户端连接。。。。。。。\n");
  pid_t pid;
  while(1){
    clie_addr_len = sizeof(clie_addr);
    cfd = accept(lfd, (struct sockaddr *)&clie_addr, &clie_addr_len);

    //打印连接客户端IP和端口号
    printf("clie IP: %s, port: %d\n",
        inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr,
          clie_IP,sizeof(clie_IP)),
        ntohs(clie_addr.sin_port));

    //创建新的进程处理这个客户端请求
    pid = fork();
    if(pid < 0){
      perror("fork error!\n");
      exit(1);
    } 
    else if(pid == 0) //子进程
    {
      close(lfd);
      break;
    }
    else{
      close(cfd);
      signal(SIGCHLD, wait_child);//回收子进程退出后，没有被释放的pcb资源
    }
  }

  if(pid == 0){
    while(1){
      n = read(cfd,buf,sizeof(buf));
      if(n == 0)//说明客户端退出连接
      {
        close(cfd);
        return 0;
      }
      else if(n == -1)
      {
        perror("read error!\n");
        return 0;
      }
      else
      {
        for(i = 0; i<n;i++)
        {
          buf[i] = toupper(buf[i]);
        }
        write(cfd,buf,n);//写回至客户端
        write(STDOUT_FILENO,buf,n);//打印至控制台（屏幕）
      }
    }
  }
  
  return 0;
}
