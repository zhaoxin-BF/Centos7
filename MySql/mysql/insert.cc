// 通过这个程序，使用mysql api来实现数据的插入功能
#include<cstdio>
#include<cstdlib>
#include<mysql/mysql.h>
// 编译器默认只在/usr/local/mysql/include这一个目录下查找
// 但是mysql.h的路径却在/usr/local/mysql/include/mysql.h下，所以我们需要写成mysql/mysql.h
// usr的全称是unix share resource   和用户没有关系

int main()
{
	// 1. 创建一个数据库连接的句柄
	MYSQL* connect_fd=mysql_init(NULL);
	// MYSQL可以猜到是一个结构体，那connect_fd就是一个结构体的指针
	// 2. 和数据库建立连接(在应用层建立)
 	// 参数：
	// a).连接的句柄
	// b).服务器的ip
	// c).用户名
	// d).密码
	// e).数据库名
	// f).服务器端口号
	// g).unix_sock NULL
	// h).client_flag 0
	// 连接失败返回空指针，成功返回非空的结果
	// 数据库连接失败很常见，所以有个判断函数很有必要
	if(!mysql_real_connect(connect_fd,"127.0.0.1",
		"root","Zhaoxin..521","blog_system",3306,NULL,0))
	{
		printf("连接失败，%s\n",mysql_error(connect_fd));
		// mysql_error can tell u why connections failed
		// this fun can translate the error code into a paragraph. 
		return 1;
	}
	printf("连接成功!\n");

	// 3.设置编码方式
	// mysql server 部分在最初安装的时候已经设置成了utf8
	// 也得在客户端设置成utf8
  mysql_set_character_set(connect_fd,"utf8");
	

	// 4.拼接sql语句
	char sql[1024*4]={0};
	char title[]="第一个项目";
	char content[]="终于开始写项目了";
	int tag_id=1;
	char date[]="2019/08/31";
	sprintf(sql,"insert into blog_table values(null,'%s','%s',%d,'%s')",title,content,tag_id,date);
	printf("插入的语句是:%s\n",sql);
	// 用户输入是不可预知的，所以为了防止用户的某些输入，造成了sql注入。我们应该采取方法来阻止这种事情的发生
	// ORM：用一个对象和数据库的一张表关联起来。防止sql注入
	// C++中的开源ORM  知名的工具安装使用比较麻烦。简单的工具又依赖非常高版本的编译器
	// 所以没有使用ORM，所以就存在SQL注入的危险


	// 5.让数据库执行拼接出的SQL
	int ret=mysql_query(connect_fd,sql);
	if(ret<0)
	{
		printf("执行SQL语句失败,%s\n",mysql_error(connect_fd));
		mysql_close(connect_fd);
		return 1;
	}
  printf("插入成功！\n");
	// 6.关闭连接
	mysql_close(connect_fd);

	return 0;
}
