
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <errno.h>

#define PORT 21
#define IP "0"
#define MAXPORT 9

#define CLIENT_PORT 22

int make_connection();

int main(){
  make_connection();
}

int make_connection(){
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr("0");

  int skt = socket( PF_INET, SOCK_STREAM, 0 );
  if (skt == -1){
    perror("socket error %d ", errno);
  
  int cnt = connect( skt, (struct sockaddr*) &addr, sizeof(addr) );
  if (cnt == -1){
    perror("cnt error %d ",errno);
  }
  
  char buf [MAXPORT + 1];
  // check weather port is taken
  itoa(CLIENT_PORT, buffer, 10);
  buf[MAXPORT] = 0;
  
  sd = send(skt, buf, MAXPORT, 0);

  if (sd == -1){
    perror("send port %d ",errno);
  }

  port2 = 0;
  rv = recv(skt, buf, MAXPORT, 0);
  if (rv == -1){
    perror("recive port2 %d", errno);
  }
  buf(MAXPORT = 0);
  
  port2 = atoi(buf);
  if (port != port2){
    perror("PORTS MISMATCH");
    exit(0);
  }
  char ok [] = "OK";
  sd = send(skt, "OK", sizeof(ok), 0);
  if (sd == -1){
    perror("send ok %d", errno);
  }
}
