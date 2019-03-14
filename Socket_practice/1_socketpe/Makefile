server:server.cc
	g++ -o $@ $^
server.cc:client
	g++ -o client client.cc
.PHONY:clean
clean:
	rm -f client server

