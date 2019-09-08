#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
  pid_t pid;
  int i;
  for(i = 0; i<5;i++)
  {
    pid = fork();
    printf("创建了一个子进程！\n");
    if(pid < 0){
      perror("fork error!\n");
    } else if(pid == 0) {
      break;
    }
  }

  if(i<5){
    sleep(i);
    printf("child process %dth pid = %d, ppid = %d\n", i, getpid(), getppid());
  } else{
    sleep(i);
    printf("father process pid = %d, ppid = %d\n", getpid(), getppid());
  }

  return 0;
}
