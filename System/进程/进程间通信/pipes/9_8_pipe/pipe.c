#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
  int fd[2];
  pid_t pid;
  int ret = pipe(fd);
  if(ret == -1){
    perror("pipe error!\n");
  }
  
  pid = fork();
  if(pid == -1){
    perror("fork error!\n");
  } else if(pid == 0){
    close(fd[1]);
    char buf[1024];
    ret = read(fd[0],buf, sizeof(buf));
    if(ret == 0){
      printf("------\n");
    }
    write(STDOUT_FILENO, buf, ret);

  } else{
    close(fd[0]);
    write(fd[1], "Hello World!\n", sizeof("Hello World!\n"));
    //sleep(1); //父进程睡眠，等待子进程读完后回收子进程
    //wait(NULL); //利用wait()阻塞等待回收子进程
    waitpid(pid,NULL,0);// 利用waitpid()指定回收子进程
  }
  return 0;
}
