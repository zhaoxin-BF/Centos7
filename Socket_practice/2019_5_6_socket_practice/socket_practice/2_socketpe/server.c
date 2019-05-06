#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<arpa/inet.h>
#include<sys/socket.h>

#define MYPORT 8080

int main()
{
	struct sockaddr_in saddr,caddr;

	char buf[1024];
	int sockfd,connfd;
	int addr_len;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	memset(&saddr,0,sizeof(saddr));

	saddr.sin_family = AF_INET;

	saddr.sin_port = htons(MYPORT);

	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr));

	listen(sockfd,20);

	printf("Accepting connections....\n");

	int n,i;
	addr_len = sizeof(caddr);
	connfd = accept(sockfd,(struct sockaddr*)&caddr,&addr_len);
    if(connfd < 0)
    {
        perror("连接出错！");
        exit(1);
    }
    printf("连接成功！\n");	
	//n = recv(connfd,buf,100,0);
	while(1)
	{
		n = read(connfd,buf,sizeof(buf));
        if(n==0)
        {
            break;
        }
		printf("Received %d bytes:%s\n",n,buf);
	}
	//n = read(connfd,buf,sizeof(buf));
	//printf("Received %d bytes:%s\n",n,buf);
    
    close(sockfd);
	close(connfd);
	return 0;
	}
