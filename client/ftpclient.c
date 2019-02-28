
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

#define CLIENT_PORT 22

int main(){
  int fd =  connect2(0,21);
  talk2(fd);
}


  
