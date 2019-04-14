#obj=main.o

target=app

#makefile中的函数的使用
src=$(wildcard ./*.c)
obj=$(patsubst ./%.c, ./%.o, $(src))

$(target):$(obj)
	gcc $(obj) -o $(target)

%.o:%.c
	gcc -c $< -o $@

#    .PHONY:声明伪目标
.PHONY:clean
clean:
	rm -f $(obj) $(target)

hello:
	echo "Hello world!"
