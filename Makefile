all: client server

client: client/client 

server: server/server

client/client: client/ftpclient.c common.c
	if gcc client/ftpclient.c -lpthread -o client/client; then \
echo "Sucecess client"; \
else \
echo "Faililure client"; \
fi

server/server: server/ftpserver.c common.c
	if gcc server/ftpserver.c -o server/server; then \
echo "Success server"; \
else \
echo "Failure server";\
fi

clean:
	rm client/client server/server
