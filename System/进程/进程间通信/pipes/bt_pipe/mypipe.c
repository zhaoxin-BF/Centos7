#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main()
{
  int fds[2];
  if(pipe(fds)<0)
  {
    printf("pipe error!\n");
    return 1;
  }
  pid_t id = fork();
  if(id == 0)
  {
    //child w
    close(fds[0]);
    const char *str = "I am child,my math is 100 !\n";
    int i = 5;
    while(i--)
    {
      write(fds[1],str,strlen(str));
      printf("child write done...\n");
      sleep(1);
    }
    close(fds[1]);
    exit(0);
  }
  else
  {
    //parent r
    close(fds[1]);
    char buff[1024];
    while(1)
    {
      ssize_t s = read(fds[0],buff,sizeof(buff)-1);
      if(s>0)
      {
        buff[s] = 0;
        printf("father recv done: %s",buff);
      }
      else if(s == 0)
      {
        printf("child quit! father quit too!\n");
        break;
      }
      else
      {}
    }
    waitpid(id,NULL,0);
  }

}
