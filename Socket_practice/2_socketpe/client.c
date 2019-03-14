#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<arpa/inet.h>
#include<netinet/in.h>

#define SERVER_IP "127.0.0.1"
#define MYPORT 8080


int main(int argc,char** argv)
{
	char buf[1024];
	char *str = "test string";

	if(argc > 1)
	{
		str = argc[1];
		}
	int cli_fd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(MYPORT);
	servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if(connect(cli_fd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0);
	{
		perror("connect fialed");
		exit(1);
		}
	printf("connect successful!\n");

	send(cli_fd,str,strlen(str)+1,0);

	close(cli_fd);

	return 0;
}
