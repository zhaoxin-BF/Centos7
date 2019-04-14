#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd;

    fd = open("ps.out",O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(fd < 0)
    {
        perror("open ps.out error");
        exit(1);
    }
    dup2(fd,STDOUT_FILENO); //dup2(3,1); fd , stdout

    execlp("ps","ps","ax",NULL);

    //close(fd);
    
    return 0;
}
