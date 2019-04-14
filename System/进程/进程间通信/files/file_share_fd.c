//父子进程间共享打开的文件描述符------使用文件完成进程间通信

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    int fd1, fd2;                            //创建两个文件描述符，分别给父进程和子进程
    pid_t pid;
    char buf[1024];                          //创建给父进程读文件的存储区
    char *str = "-----------test for shared fd in parent chaild process----------\n";

    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        fd1 = open("test.txt",O_RDWR);       //打开文件
        if (fd1 < 0) {
            perror("open error");
            exit(1);
        }
        write(fd1, str, strlen(str));        //向文件写入str
        printf("child worte over...\n");
    } else {
        fd2 = open("test.txt", O_RDWR);      //父进程打开文件
        if(fd2 < 0) {
            perror("open error");
            exit(1);
        }
        sleep(1);

        int len = read(fd2, buf, sizeof(buf));//父进程读文件
        write(STDOUT_FILENO, buf, len);       //标准输出到终端

        wait(NULL);                           //阻塞回收，防止僵尸进程
    }
    return 0;
}
