/*
1) listen 21
2)if connected create inf connection to client
3)transfer 22
*/


//TODO FIX COMPLILE ERRORS -> VIEW client TODO -> ...

#define SERVER_PORT 21

#ifndef SIZE
#define SIZE 1000
#endif

// TODO:
/*
*/
//TODO



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

#include<dirent.h>


#ifndef COMMON
#define COMMON
#include "../common.c"
#endif


void talk2client(int socket);

int main(){
  int port = htons(SERVER_PORT);
  int fd = open_port(port);
  send_file_list(fd);
  /*
  if (fd != -1)
    talk1(fd);
  */
  
}



void send_file_list(int skt){
  char buf[1000];
  DIR *dir;
  struct dirent *ent;
  if((dir = opendir(".")) != NULL ){
      while ((ent == readdir(dir)) != NULL){
        //TODO send ent->d_name
	int n = strnlen(ent->d_name, SIZE - 1);
	//send_string(ent->d_name,n,skt);
	//send_string("hi",2,skt);
	//printf("%s\n",ent->d_name);
      }
    }
}
//send string no more than n  bytes(chars) including zero
void send_string(char *s,int n,int sk){
  while(n >= 0){
    int size = min(n,SIZE);
    int k = 0;
    while(k < size){
      int n1  = send(sk,s,size,0);//<-TODO n <- size
      k+=n1;
    }
    n-=size;
  }
}
