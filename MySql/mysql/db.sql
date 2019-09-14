#需要创建两张表

#表1：创建一个博客文章表 blog_table;
#blog_id int
#title varchar(50)
#content text
#create_time varchar(50)
#tag_id int             //博客的tag(标签)

#表2：创建一个博客标签表 blog_tag;
#tag_id int
#tag_name varchar(50)
#

drop database if exists blog_system;
create database blog_system;

use blog_system;
drop table if exists blog_table;
create table blog_table(
  blog_id int not null primary key auto_increament,
  tile varchar(50),
  content text,
  tag_id int,
  create_time varchar(50)
);

drop table exists blog_tag;
create table tag_table(
  tag_id int not null primary key auto_increament,
  tag_name varchar(50)
);


#执行的语句
#mysql -u root < mariadb.sql
#利用重定向把标准输出来进行重定向
# < 是标准输入重定向
# 标准错误重定向是2>
