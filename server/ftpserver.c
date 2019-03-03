/*
1) listen 21
2)if connected create inf connection to client
3)transfer 22
*/


int open_port(int PORT);
int transfer();

#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

#include<unistd.h>
#include<stdio.h>

#include<errno.h>

#include "../common.c"


void talk2client(int socket);

int main(){
  int fd = open_port(21);
  /*
  if (fd != -1)
    talk1(fd);
  */
}

int open_port(int PORT){
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  
  int skt = socket(PF_INET, SOCK_STREAM, 0);
  printf("hi\n");
  bind(skt, (struct sockaddr*) &addr, sizeof(addr));
  
  if(listen(skt, 0) == -1){
    perror("listen ");
    return -1;
  }
  struct sockaddr_storage addr_s;

  memset(&addr_s, 0, sizeof(addr_s));

  int addr_size = sizeof(addr_s);
  int fd = accept( skt, (struct sockaddr*) &addr_s, &addr_size);
  if (fd == -1){
    perror("accept");
  }
  
  if (fd != 0){
  }
  return fd;  
  
}


//TODO


/*
void talk (int socket){
  
  
  char buf[MAXPORT + 1];
  rv = recv(fd, buf, MAXPORT, 0);
  if (rv == -1){
    perror("recive port %d", errno);
  }
  buf[MAXPORT] = 0;
  int port = atoi(buf);
  printf("%d\n", port);
  return 0;

  itoa(port, buffer, 10);
  buf[MAXPORT] = 0;
  
  sd = send(skt, buf, MAXPORT, 0);

  if (sd == -1){
    perror("send port %d ",errno);
  }

  char buf[MAXPORT + 1];
  rv = recv(fd, buf, MAXPORT, 0);
  if (rv == -1){
    perror("recive ok  %d", errno);
  }
  buf[2] = 0;
  if (strncmp(buf, "ok", 2) == 0){
    printf("OK");
  }
  else {
    perror("WRONG CLIENT PORT");
  }
}

*/
