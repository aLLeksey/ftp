#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <errno.h>
#include <stdio.h>

#include <pthread.h>


#ifndef COMMON
#define COMMON
#include "../common.c"
#endif

#ifndef SIZE
#define SIZE 1000
#endif

#define MAXPORT 9

#define CLIENT_PORT 7777
//#define SERVER_PORT 9999
#define SERVER_PORT 21

#define CLIENT_IP 0
#define SERVER_IP 0

void rcv_and_print_file_list(int sck);

//TODO 
int client_listen_fd; //WHAT is it??? 

int main(){
  int port = htons(SERVER_PORT);
  int sk =  connect2(SERVER_IP,port);
  if (sk == -1){
    return 0;
  }

  pthread_t tid1;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid1,&attr,rcv_and_print_file_list,sk);
  
  
  char *buf=NULL;
  int n=0;
  while(1){
    int k = getline(&buf,&n,stdin);// \n\0 <- include
    // k = count without '\n'
    if(send(sk,buf,k+1,0) == -1){
      perror("send error");
    }
  }

  pthread_join(tid1, NULL);
  
  //talk_send(sk);
  // talk_recv(sk);
  /*
  client_listen_sk = open_port(CLIENT_PORT);
  */
}


  
void send_prt_ip_server(int fd){
  int ip = htonl(CLIENT_IP);
  int port = htons(CLIENT_PORT);

  send(fd,(char *)&port,sizeof(int),0);
  send(fd,(char *)&ip,sizeof(int),0);
}
void recv_prt_ip_server(int sck, int *port, int *ip){
  recv(sck, ip, sizeof(int), 0);
  recv(sck, port, sizeof(int), 0);
}
void send_file(int skt, int fd){//another thread+ not thread version
  char buf[1000];
  int sz = sizeof(buf)/sizeof(buf[0]);
  int l = 0;
  do{
    l = read(fd, buf, sz);
    if(l == -1){
      break;
    }
    int k = 0;
    while(k != l){
      int n  = send(skt,buf,sz,0);
      k+=n;
    }
    if(l < sz){
      break;
    }
  }while(1);
  
}

void  recv_file(int sck, int fd){//another thread+ not thread version
  char buf[SIZE];
  int l = 0;
  int sz = sizeof(buf)/sizeof(buf[0]);
  do{
    l = recv(sck, buf, sz,0);
    if(l == -1){
      break;
    }
    int k = 0;
    while(k != l){
      int n  = write(fd,buf,l);
      k+=n;
    }
    if(l < sz){
      break;
    }
  }while(1);
}

void recv_smth(int skt, char * BUF, int len){
  int l = 0;
  int sz = len;
  //do{
    l = recv(skt, BUF, sz,0);
    if ( l > sz){
      perror("RECV to much...\n more than BUF");
      exit(1);
      //l = sz;
      //BUF[l] = 0;
      
    }
    BUF[l] = 0;
    //   if(l == -1){
    //     break;
    //   }
    // }while(1);
}
  

  
	

void rcv_and_print_file_list(int skt){
  char buf[SIZE];
  while(1){
    recv_smth(skt,buf,SIZE - 1);
    buf[SIZE-1] = 0;
    printf("%s",buf);
  } 
 
}
//nc connect
//nc localhost 21
//nc listen
//sudo nc -l 21

//0 connect client server
//#connect nc server +
//#connect client nc +
//#send(!)/recv smth nc (!!!) + done
//#talk client nc +-
//#################
//it FUCKING recvs(different thread) but not sends !!!!! +-
//#####################
// recv's/sends but with problem +-
//#connect client server (client segfal)-

//TODO LIST
//
//
//SHOW FILES LIST FROM SERVER IN CLIENT(!!!!)


// FIX COMPILE ERRORS

/* recv IP/PORT -> new thread -> wait till file recv request-> recv_file */
// check with nout c + Python old

//show catalog(client)
// check with nout c + Python old

//be able choose file to download

// navigate catalog
// add telnet commands
