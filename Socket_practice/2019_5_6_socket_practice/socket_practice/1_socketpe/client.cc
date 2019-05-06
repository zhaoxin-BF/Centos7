#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>




#define SERV_IP "172.17.98.161"
#define SERV_PORT 5555

using namespace std;

int main(void)
{
	int cfd;
	struct sockaddr_in serv_addr;
	char buf[BUFSIZ];
	int n;
    
    cfd=socket(AF_INET,SOCK_STREAM,0);

    memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERV_PORT);
	inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);

	//connect(cfd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr));
	int ret = connect(cfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    if(ret < 0)
    {
        perror("connect error!");
        exit(1);
    }

	while(1)
	{
		// cout<<"输入一个值：";
		// fgets(buf,sizeof(buf),stdin);		//fgets的时候，用户输入hello回车，读取之后的结果就是"hello\n\0"所以在write中可以直接用strlen(buf)来求长度。
		// cout<<"test1";
		// write(cfd,buf,strlen(buf));
		// cout<<"2rd test";
		// n=read(cfd,buf,sizeof(buf));
		// write(STDOUT_FILENO,buf,n);
		// cout<<"End test!"<<endl;
		cout<<"请输入数据测试数据小写字母！"<<endl;
		cin>>buf;
		write(cfd,buf,strlen(buf));
        n = read(cfd,buf,sizeof(buf));
		write(STDOUT_FILENO,buf,n);
        cout<<endl;
	}

	close(cfd);
	return 0;
}
