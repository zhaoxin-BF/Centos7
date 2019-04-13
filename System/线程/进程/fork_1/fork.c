#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    pid_t pid;

    int i;
    for(i = 0; i< 4; i++)
    {
        printf("-------------------%d\n",i);
    }
    
    pid = fork();
    if(pid == 0)
    {
        printf("Child process ,pid = %d, ppid = %d\n",getpid(),getppid());
        exit(0);
    }
    else
    {
        printf("Parent process ,pid = %d\n",getpid());
        sleep(1);
    }
    for(i = 0;i < 4; i++)
    {
        printf("*******************%d\n",i);
    }
    return 0;
}
