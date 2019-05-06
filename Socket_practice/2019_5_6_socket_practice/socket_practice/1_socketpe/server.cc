//这是一个小写转大写程序。client发送小写字母到server端。Server转成大写之后再返回给Client
//
//
//在server端运行测试的时候，另开窗口使用指令nc 127.0.0.1 6666   输入即可测试
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<stdlib.h>
#include<ctype.h>


#define SERV_IP "172.17.98.161"
#define SERV_PORT 5555											//端口值不能大于65535，不小于1000（1000以下的一般给系统用）
using namespace std;

int main(void)
{
	int lfd,cfd;												//socket返回的文件描述符
	struct sockaddr_in serv_addr,clie_addr;						//socket总是成对出现
	// struct sockaddr
	// {
	// 	sa_family_t sa_family;									//协议类型	
	// 	char sa_data[14];										
	// };	
	// 
	// 
	// struct sockaddr_in
	// {
	// __kernel_sa_family_t sin_family; 		/* Address family */  	地址结构类型
	// __be16 sin_port;					 		/* Port number */   	16位端口号
	// struct in_addr sin_addr;					/* Internet address */	32位	IP地址
	// /* Pad to size of `struct sockaddr'. */
	// unsigned char __pad[__SOCK_SIZE__ - sizeof(short int) -
	// sizeof(unsigned short int) - sizeof(struct in_addr)];
	// };
	// struct in_addr {						/* Internet address. */
	//__be32 s_addr;
	//};

	




	socklen_t clie_addr_len;									//accept函数中的参数
	
	char buf[BUFSIZ];											//BUF是操作系统内嵌的宏    #define BUFSIZ _IO__HUFSIZ
	int n,i;													//read的返回值

	lfd=socket(AF_INET,SOCK_STREAM,0);							//建立socket套接字
	//参数：	1.用IPV4的地址
	//		2.使用TCP协议来传输（如果使用参数SOCKET_DGRAM就是使用UDP协议）
	//		3.表示使用默认协议
	//	 

	serv_addr.sin_family = AF_INET;  							//指定所采用的地址类型是ipv4,ipv6还是本地局域网(此处应该和socket函数的取值相同)

	serv_addr.sin_port = htons(SERV_PORT);						//设置端口号，并使用htons函数将小端数据转成大端来存储

	serv_addr.sin_addr.s_addr= htonl(INADDR_ANY);				//INADDR_ANY是一个宏，绑定一个本地有效的任意IP（这个IP是unsigned int类型）

	bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));	//向套接字绑定IP和端口号
	//参数：	1.socket的返回值
	//		2.类型为sockaddr_in类型的结构体
	//		3.类型为socklen_t类型的长度
	
	
	listen(lfd,128);											//允许同时有128个客户端发起连接
	//参数：	1.socket文件描述符
	//		2.可同时发起连接的客户端个数
	clie_addr_len=sizeof(clie_addr);
	cfd=accept(lfd,(struct sockaddr *)&clie_addr,&clie_addr_len);				//accept之后，server程序就会阻塞等待
	if(cfd < 0)
    {
        cout<<"连接出错！"<<endl;
        exit(1);
    }
    cout<<"连接成功！"<<endl;
    //第二个参数是传出参数
	//在这里的第三个参数是传入传出参数。所以必须先定义好这个socklen_t类型，而bind函数的第三个参数就不用
	//传入的参数，需要在传入之前先初始化好有个实际值
	//传出的参数，要加&取地址
	while(1)
	{
		n=read(cfd,buf,sizeof(buf));
		if(n==0)
		{
			break;
		}
		cout<<"收到信息：";
		for(i=0;i<n;i++)
		{
			cout<<buf[i];
			buf[i]=toupper(buf[i]);
		}
        cout<<endl;
        cout<<"转换之后：";
		for(i=0;i<n;i++)
		{
			cout<<buf[i];
		}
		write(cfd,buf,n);
        cout<<endl;
	}
	close(lfd);
	close(cfd);
	return 0;
}
 
