#ifndef DEBUG
#define DEBUG
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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
void keyboard_send(int sck);

void send_string_a(const char *s,int n,int sck);
void recv_smth2(int skt);


//TODO 
int client_listen_fd; //WHAT is it??? 

int main(){
  int port = htons(SERVER_PORT);
  int sck =  connect2(SERVER_IP,port);
  if (sck == -1){
    return 0;
  }
  /*
// TO CHECK IF THEADING AFFECTS.
// ANSWER: DOESNT' MATTER. STILL NOT WORKING.
  pthread_t tid1;// recv text
  pthread_attr_t attr1;
  pthread_attr_init(&attr1);
  pthread_create(&tid1,&attr1,recv_smth2,sck);

  pthread_t tid2;// send text
  pthread_attr_t attr2;
  pthread_attr_init(&attr2);
  pthread_create(&tid2,&attr2,keyboard_send,sck);
  
 
  pthread_join(tid2, NULL);
  pthread_join(tid1, NULL);
  */
  //talk_send(sk);
  // talk_recv(sk);
  /*
  client_listen_sk = open_port(CLIENT_PORT);
  */
  recv_smth2(sck);
}


void keyboard_send(int sck){
  char *buf=NULL;
  size_t n=0;
  while(1){
    int k = getline(&buf,&n,stdin);// buf,n -< \n\0 <- include
    // k = count with '\n' without '\0'
    send_string_a(buf, k + 1 , sck);
  }
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
//TODO FIXp;
void send_string_a(const char *s,int n,int sck){
  while(n > 0){
    int size = min(n,SIZE);
    n-=size;
    while(size >0){
      int k  = send(sck,s,size,0);
      if ( k == -1){
	perror("send string error");
	sleep(5);
	k = 0;
	//exit(1);
      }
      s = s+k;//<-TODO TEST.  NEED to add k??? 
      size-=k;
    }
    
  }
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
    l = recv(skt, BUF, sz,0);
    if ( l > sz){
      perror("RECV to much...\n more than BUF");
      exit(1);    
    }
    BUF[l] = 0;
}
void recv_smth2(int skt){
  char BUF[SIZE];
  while(1){
    int l = recv(skt,BUF,SIZE-1,0);
    if(l == -1){
      perror("recv error");
    }
    BUF[l] = 0;
    printf("%s", BUF);
  }
}


  
	

void rcv_and_print_file_list(int skt){
  char buf[SIZE];
  while(1){
    recv_smth(skt,buf,SIZE-1);
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
//#talk client nc +
//#################
//it FUCKING recvs(different thread) but not sends !!!!! +
//#####################
//send/recv different thread(later may be change that)+
// recv's/sends but with problem (possible BUGS) +-
//#connect client server (client segfal)-
//TODO ^ (show files client NOT wokring)
// Threading doesn't matter: still NOT working


//TODO LIST
//
//
//SHOW FILES LIST FROM SERVER IN CLIENT(!!!!)

//send/recv different thread(later may be change that)+

// FIX COMPILE ERRORS

/* recv IP/PORT -> new thread -> wait till file recv request-> recv_file */
// check with nout c + Python old

//show catalog(client)
// check with nout c + Python old

//be able choose file to download

// navigate catalog
// add telnet commands
