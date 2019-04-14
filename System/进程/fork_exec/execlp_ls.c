#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    if(pid == -1){
        perror("fork error!\n");
        exit(1);
    } else if(pid > 0) {
        sleep(1);
        printf("parent\n");   
    } else {
        
        //一般来说调用系统可执行程序，例如ls等
        //execlp("./test","test",NULL);
        execlp("ls","ls","-l","-a",NULL);

        //一般来说调用用户自定义可执行程序
        //execl("/bin/ls","ls","-l","-a",NULL);

        //execl("./test","test",NULL);

        /*
        char *argv[] = {"ls","-l",NULL};
        execv("/bin/ls",argv); 
        */
    }
    return 0;
}
