#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1){
        perror("pipe error!\n");
        exit(1);
    }
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error!\n");
        exit(1);
    } else if(pid  == 0) { //子进程读，需关闭写端，人为规定1为写端，0 为读端
        sleep(1);
        close(fd[1]);
        char buf[1024];
        ret = read(fd[0], buf, sizeof(buf));
        if (ret == 0) {
            printf("--------\n");
        }
        write(STDOUT_FILENO, buf, ret);
    } else {               //父进程写，需要关闭读端f[0]端
        close(fd[0]);
        write(fd[1], "hello pipe\n", strlen("hello pipe\n"));
        wait(NULL);
    }
    return 0;
}
