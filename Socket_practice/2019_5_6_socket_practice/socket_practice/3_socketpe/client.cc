#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAXLINE 80
#define SERV_PORT 6666

using namespace std;
int main()
{
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int sockfd,n;
	char str[] = "hello world";
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET,"172.17.98.161",&servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	int ret = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    if(ret <0)
    {
        perror("连接出错！");
        exit(1);
    }
    
    cout<<"连接成功服务器成功！"<<endl;
	write(sockfd,str,strlen(str));
	n=read(sockfd,buf,strlen(str));
	cout<<"Response from server:"<<endl;

	write(STDOUT_FILENO,buf,n);
	close(sockfd);
	return 0;
	}

