.PHONY:all 
all:insert select

insert:insert.cc 
	g++ -o $@ $^ -L/usr/lib64/mysql  -lmysqlclient -fpermissive

select:select.cc 
	g++ $^ -o $@ -L/usr/lib64/mysql -lmysqlclient 

.PHONY:clean
clean:
	rm -f insert
