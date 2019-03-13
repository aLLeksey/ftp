/*
1) listen 21
2)if connected create inf connection to client
3)transfer 22
*/


//TODO FIX COMPLILE ERRORS -> VIEW client TODO -> ...

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
  int port = htons(21);
  int fd = open_port(port);
  void send_file_list(fd);
  /*
  if (fd != -1)
    talk1(fd);
  */
  
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
