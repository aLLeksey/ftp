#define SIZE 1000
#define COMMON

#define DEBUG

#define min(x,y) ((x) < (y)) ? (x) : (y)


//TODO add and fill common.h
//and add headers

void talk_recv(int socket){
  char buf[SIZE];
  while(1){
    int k = recv(socket,buf,SIZE-1,0);//SIZE-1 <=> plase for ZERO byte
    buf[k] = 0;
    printf("%s",buf);
  }
}

void talk_send(int socket){
  char buf[SIZE]="lala";
  send(socket,buf,4,0);
  /*
  char buf[SIZE]="lala";
  int n = strnlen(buf,SIZE);
  while(1){
    int k = send(socket,buf,n,0);
  }
  */
}




int string2ip(const char *s){
  struct sockaddr_in sa;
  memset(&sa,0,sizeof(sa));
  inet_pton(AF_INET, s, &(sa.sin_addr));
  return (int)sa.sin_addr.s_addr;
}
void ip2string(int ip, char** s){
  inet_ntop(AF_INET,&ip,*s,INET_ADDRSTRLEN);
}


int connect2(int IP, int PORT){
  //^ in network byte order^
  
  // int ip = htonl(IP);  
  // int port = htons(PORT);
  
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = PORT;
  addr.sin_addr.s_addr = IP;

  int skt = socket( PF_INET, SOCK_STREAM, 0 );
  if (skt == -1){
    perror("socket error");
  }
  int cnct = connect( skt, (struct sockaddr*) &addr, sizeof(addr) );
  if (cnct == -1){
    perror("cnct error");
    return -1;
  }
  return cnct;
}



int connect4rom(int PORT){
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




// all in network byte order
int open_port(int PORT){
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  //addr.sin_port = htons(PORT);
  addr.sin_port = PORT;
  
  int skt = socket(PF_INET, SOCK_STREAM, 0);

  int enable = 1;
  if(setsockopt(skt,SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)))
     perror("setsockopt(SO_REUSEADDR)failed");
#ifdef DEBUG
  printf("hi\n");
#endif
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
