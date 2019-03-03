
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <errno.h>
#include <stdio.h>

#include "../common.c"

#define MAXPORT 9

#define CLIENT_PORT 7777
#define SERVER_PORT 9999

#define CLIENT_IP 0
#define SERVER_IP 0

int client_listen_fd;

int main(){
  int fd =  connect2(SERVER_IP,SERVER_PORT);
  if (fd == -1){
    return 0;
  }
  talk2(fd);
  client_listen_fd = open_port(CLIENT_PORT);
}


  
void send_prt_ip_server(int fd){
  int ip = htonl(CLIENT_IP);
  int port = htons(CLIENT_PORT);

  send(fd,port,sizeof(int),0);
  send(fd,ip,sizeof(int),0);
}
void recv_prt_ip_server(int sck, int *port, int *ip){
  recv(sck, *ip, sizeof(int), 0);
  recv(sck, *port, sizeof(int), 0);
void send_file(int sck, int file){//another thread+ not thread version
  char buf[1000];
  int l = 0;
  //TODO change 1000 -> sizeof(BUFF)
  do{
    l = read(fd, buf, 1000);
    int k = 0;
    while(k != l){
      int n  = send(skt,buf,1000,0);
      k+=n;
    }
  
}

void  recv_file(int sck, int fd, int size){//another thread+ not thread version
  char buf[1000];
  int l = 0;
  //TODO change 1000 -> sizeof(BUFF)
  do{
    l = recv(sck, buf, 1000,0);
    int k = 0;
    while(k != l){
      int n  = write(fd,buf,l);
      k+=n;
    }
}

void send_file_list(int sck){
  char buf[1000];
  DIR *dir;
  struct dirent *ent;
  if((dir = opendir(".")) != NULL ){
      while ((ent == readdir(dir)) != NULL){
        //TODO send ent->d_name
	snprintf(buf,1000,"%s\n",ent->d_name);
	do{
	  l = read(fd, buf, 1000);
	  int k = 0;
	  while(k != l){
	    int n  = send(skt,buf,1000,0);
	    k+=n;
	  }
	}
      }
    }
}

  
	

void rcv_and_print_file_list(int sck){
}

/* recv IP/PORT -> new thread -> wait till file recv request-> recv_file */
// check with nout c + Python old
