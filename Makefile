all: client server

client: client/client 

server: server/server

client/client: client/ftpclient.c
	gcc client/ftpclient.c -o client/client
server/server: server/ftpserver.c
	gcc server/ftpserver.c -o server/server
clean:
	rm client/client server/server
