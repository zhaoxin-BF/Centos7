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
        
        //execlp("./test","test",NULL);

        //execl("/bin/ls","ls","-l","-a",NULL);

        //execl("./test","test",NULL);

        char *argv[] = {"ls","-l",NULL};
        execv("/bin/ls",argv); 
    }
    return 0;
}
