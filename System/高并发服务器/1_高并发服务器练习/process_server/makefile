server:server.c
	gcc -o $@ $^
server.c:client
	gcc -o client client.c
.PHONY:clean
clean:
	rm -f server client

