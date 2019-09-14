# 一、MySQL C API  安装(通过yum进行安装，不要用手动安装费时费力，投入产出比不行)

## 1、查看需要安装的包
	#yum list | grep mysql
	
## 2、安装下面这个编程工具包
	#yum install mysql++-devel.x86_64                       3.1.0-12.el7           @epel 
	
## 3、安装好后在# cd /usr/include/mysql目录下，会有一个mysql文件夹，里面包含了mysql C API .h文件

     在# cd /usr/lib64/mysql 目录下，会有mysql客户端的相关文件
libmysqlclient.a        libmysqlclient_r.so.18.1.0  libmysqlclient.so.18      libmysqlclient.so.20       libmysqlservices.a  plugin
libmysqlclient_r.so.18  libmysqlclient.so           libmysqlclient.so.18.1.0  libmysqlclient.so.20.3.14  mecab
##4、如何使用得查看MySQL API 文档。

## 5、配置好MySQL C API 文件后，在使用mysql.h时 ，这样包含#include <mysql/mysql.h> 
	因为在/user/include/目下没有直接的mysql.h 他是在mysql/mysql.h

# 二、使用MySQL C API 用例
## 插入数据库 

```C++
/////////////////////////////////////////////////////// 
// 编译选项 
// -L /usr/lib64/mysql -lmysqlclient 
// 删除, 更新 和插入同理, 只是拼装成不同的 SQL 而已 
/////////////////////////////////////////////////////// 
#include <cstdio> 
#include <cstdlib> 
#include <mysql/mysql.h> 
int main() { 
// 1. 初始化句柄 
MYSQL* connect_fd = mysql_init(NULL); 
// 2. 建立链接 
// mysql_init 返回的指针 
// 主机地址 
// 用户名 
// 密码 
// 数据库名// 端口号 
// unix_socket 
// client_flag 
if (mysql_real_connect(connect_fd, "127.0.0.1", "root", "", 
"blog_system", 3306, NULL, 0) == NULL) { 
printf("连接失败! %s\n", mysql_error(connect_fd)); 
return 1; 
}
// 3. 设置编码格式 
mysql_set_character_set(connect_fd, "utf8"); 
// 4. 拼装 SQL 语句 
char sql[1024 * 4] = {0}; 
char title[] = "立一个 flag"; 
char content[] = "我要拿 30w 年薪"; 
int tag_id = 2; 
char datetime[] = "2019/05/14 12:00"; 
sprintf(sql, "insert into blog_table values(null, '%s', '%s', %d, '%s')", 
title, content, tag_id, datetime); 
// 5. 执行 SQL 语句 
int ret = mysql_query(connect_fd, sql); 
if (ret < 0) { 
printf("执行 sql 失败! %s\n", mysql_error(connect_fd)); 
return 1; 
}
// 6. 关闭句柄 
mysql_close(connect_fd); 
printf("执行成功!\n"); 
return 0; 
} 
```
## 查找数据库 
```C++
mysql_select.cc 
/////////////////////////////////////////////////////// 
// 编译选项 
// -L /usr/lib64/mysql -lmysqlclient 
// 删除, 更新 和插入同理, 只是拼装成不同的 SQL 而已 
/////////////////////////////////////////////////////// 
#include <cstdio> 
#include <cstdlib> 
#include <mysql/mysql.h> 
int main() { 
// 1. 初始化句柄 
MYSQL* connect_fd = mysql_init(NULL); 
// 2. 建立链接 
// mysql_init 返回的指针 
// 主机地址 
// 用户名 
// 密码 
// 数据库名
// 端口号 
// unix_socket 
// client_flag 
if (mysql_real_connect(connect_fd, "127.0.0.1", "root", "", 
"blog_system", 3306, NULL, 0) == NULL) { 
printf("连接失败! %s\n", mysql_error(connect_fd)); 
return 1; 
}
// 3. 设置编码格式 
mysql_set_character_set(connect_fd, "utf8"); 
// 4. 拼装 SQL 语句 
char sql[1024 * 4] = {0}; 
sprintf(sql, "select * from blog_table"); 
// 5. 执行 SQL 语句 
int ret = mysql_query(connect_fd, sql); 
if (ret < 0) { 
printf("执行 sql 失败! %s\n", mysql_error(connect_fd)); 
return 1; 
}
// 6. 遍历查询结果 
MYSQL_RES* result = mysql_store_result(connect_fd); 
if (result == NULL) { 
printf("获取结果失败! %s\n", mysql_error(connect_fd)); 
return 1; 
}
// a) 获取行数和列数 
int rows = mysql_num_rows(result); 
int fields = mysql_num_fields(result); 
printf("rows: %d, fields: %d\n", rows, fields); 
// b) 打印结果 
for (int i = 0; i < rows; ++i) { 
MYSQL_ROW row = mysql_fetch_row(result); 
for (int j = 0; j < fields; ++j) { 
printf("%s\t", row[j]); 
}
printf("\n"); 
}
// 7. 释放结果集 
mysql_free_result(result); 
// 8. 关闭句柄 
mysql_close(connect_fd); 
printf("执行成功!\n"); 
return 0; 
}
```
