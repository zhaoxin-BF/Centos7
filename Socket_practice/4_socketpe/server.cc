#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

//#define SERV_IP "172.17.98.161"
#define SERV_PORT 6666

int main()
{

	int lfd,cfd;
	struct sockaddr_in serv_addr,clie_addr;
	socklen_t clie_addr_len;
	char buf[BUFSIZ],clie_IP[BUFSIZ];

	int n ,i;
	lfd = socket(AF_INET,SOCK_STREAM,0);//创建Socket

	bzero(&serv_addr,sizeof(serv_addr));//清空缓冲区，引用+所需清空大小

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

	listen(lfd,128);

	clie_addr_len = sizeof(clie_addr);
	cfd = accept(lfd,(struct sockaddr *)&clie_addr,&clie_addr_len);//等待客户端连接

	printf("client IP :%s ,client port :%d\n",
			inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_IP,sizeof(clie_IP)),
			ntohs(clie_addr.sin_port));

	while(1)
	{
		n = read(cfd,buf,sizeof(buf));
		for(i = 0;i<n; i++)
		{
			buf[i] = toupper(buf[i]);
		}
		write(cfd,buf,n);
	}
	close(lfd);
	close(cfd);

	return 0;
}
