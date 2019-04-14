#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


//wait: 阻塞回收子进程
//wait（status）： 返回成功pid ,失败：返回-1；
//status：传出参数（阻塞等待子进程，回收子进程资源，获取子进程结束状态）

//waitpid: 回收指定子进程
//参1：
//          pid > 0 指定子进程ID 回收
//          pid = -1 回收任意子进程（wait）
//          pid = 0 回收本组任意子进程
//          pid < -1 回收该进程组的任意进程
//参2：     status
//参3:       0： （wait）阻塞回收

int main()
{
    pid_t pid,wpid;
    int status;

    pid = fork();
    if(pid == -1){
        perror("fork error!\n");
        exit(1);
    } else if (pid > 0){
        wpid = wait(&status);
        if (wpid == -1)
        {
            perror("wait error!\n");
            exit(1);
        }
        
        //WIFSIGNALED（）真
        //  WIERMSIG（） 获取导致子进程终止的信号的编号
        if(WIFSIGNALED(status)) {
           printf("child killed by %d\n", WTERMSIG(status));
        }

        //WIFEXITED（） 真
        //  WEXITSTATUS（） 获取子进程退出状态
        /*if(WIFEXITED(status)) {
            printf("child exit whit %d\n", WEXITSTATUS(status));
        }*/

        while(1){
            printf("I'm parent pid = %d, parentID = %d\n",getpid(),getppid());
            sleep(1);
        }
    } else {

        printf("Child pid = %d, parentId = %d\n",getpid(),getppid());
        sleep(60);
        printf("----------child die-----------\n");
        //exit(75);
        return 100;
    }
    return 0;
}
