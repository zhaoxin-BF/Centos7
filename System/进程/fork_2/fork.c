#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int number = 5;
    pid_t pid;
    int i,count=0;
    for(i = 0;i<number; i++)
    {
        if(pid > 0)
            sleep(1);
        printf("i = %d ,pid = %d, ppid = %d\n",i,getpid(),getpid());
        pid = fork();
    }
    return 0;
}
