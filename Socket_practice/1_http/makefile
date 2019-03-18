.PHONY:all clean
all:http_server
http_server:http_server.c
	gcc $^ -o $@ -lpthread
clean:
	rm -rf http_server
