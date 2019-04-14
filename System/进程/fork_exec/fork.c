#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    if(pid == -1){
        perror("fork error!\n");
        exit(1);
    } else if (pid > 0){
        sleep(2);
        printf("I'm parent pid = %d, parentID = %d\n",getpid(),getppid());
    } else {
        printf("Child pid = %d, parentId = %d\n",getpid(),getppid());
    }
    return 0;
}
