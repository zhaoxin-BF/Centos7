#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<arpa/inet.h>
#include<netinet/in.h>

#define SERVER_IP "172.17.98.161"
#define MYPORT 8080


int main()
{
	char buf[1024];
	char *str = "test string";
	int cli_fd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in servaddr;

	memset(&servaddr,0,sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(MYPORT);
	inet_pton(AF_INET,SERVER_IP,&servaddr.sin_addr.s_addr);

    int ret = connect(cli_fd,(struct sockaddr *)&servaddr, sizeof(servaddr));
	if(ret < 0)
    {
        perror("连接出错！");
        exit(1);
    }

    printf("connect successful!\n");
    

    //write(cli_fd,str,strlen(str)+1);
    send(cli_fd,str,strlen(str)+1,0);
	close(cli_fd);

	return 0;
}
