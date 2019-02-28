void talk2(int socket){
  char buf[1000];
  while(1){
    int k = recv(socket,buf,999,0);
    buf[k] = 0;
    printf("%s",k);
  }
}

void talk1(int socket){
  char buf[1000]="lala";
  int n = strnlen(buf,1000);
  while(1){
    int k = send(socket,buf,n,0);
  }
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
  int ip = htonl(IP);
  int port = htons(PORT);
  
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = ip;

  int skt = socket( PF_INET, SOCK_STREAM, 0 );
  if (skt == -1){
    perror("socket error");
  }
  int cnct = connect( skt, (struct sockaddr*) &addr, sizeof(addr) );
  if (cnct == -1){
    perror("cnct error");
  }
  return -1;
}
