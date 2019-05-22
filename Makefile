all: client server

client: client/client 

server: server/server

client/client: client/ftpclient.c common.c
	gcc client/ftpclient.c -lpthread -o client/client
server/server: server/ftpserver.c common.c
	gcc server/ftpserver.c -o server/server
clean:
	rm client/client server/server
