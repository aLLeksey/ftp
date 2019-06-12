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
#include<stdlib.h>

#include<errno.h>

#include<dirent.h>
#include<sys/stat.h>

#ifndef COMMON
#define COMMON
#include "../common.c"
#endif


void talk2client(int socket);
int is_directory(const char *path);
void send_string(const char *s,int n,int sk);
void send_file_list(int skt);

int main(){
  //TODO  
  int port = htons(SERVER_PORT);
  int sk = open_port(port);
  if (sk == -1){
    perror("can't open port");
  }
  
  send_string_2("Hello!\n", sizeof("Hello!\n"), sk);
  send_file_list(sk);
  
  /*
  if (fd != -1)
    talk1(fd);
  */
  
}



void send_file_list(int skt){
  char buf[SIZE];
  DIR *dir;
  struct dirent *ent;
  if((dir = opendir(".")) != NULL ){
      while ((ent = readdir(dir)) != NULL){
	int n = strnlen(ent->d_name, SIZE - 2);//without \0
	//snprintf(buf,n+2,"%s\n",ent->d_name);//\n\0
	snprintf(buf,n+1,"%s",ent->d_name);//\n\0
	//send_string(buf,min(n+2,SIZE),skt);
	send_string(buf,n+1,skt);
	
	// strangelly works only with printf + input
	// WHYWHYWHY???
	// TODO MAKE IT WORK
      }
    }
}
//send string no more than n  bytes(chars) including zero
void send_string(const char *s,int n,int sk){
  while(n > 0){
    int size = min(n,SIZE);
    n-=size;
    while(size > 0){
      int n1  = send(sk,s,size,0);
      if(n1 == -1){
	perror("cant' send");
	sleep(5);
	n1 = 0;
      }
      s+=n1;
      size-=n1;
    }
  }
}
void send_string_2(const char *s, int n, int sk){
  send(sk,s,n,0);
}

///Send File List Second Edtn////////////

int select_dir(const struct dirent* a){
  return is_directory(a->d_name);
}
int select_not_dir(const struct dirent* a){
  return !select_dir(a);
}


int is_directory(const char *path){
  struct stat stat_buf;
  if(stat(path, &stat_buf) != 0){
    return 0;
  }
  return S_ISDIR(stat_buf.st_mode);
}


int print_dir(int (*filter)(const struct dirent *)){
  struct dirent **eps;
  int n;

  n = scandir ("./", &eps, filter, alphasort);
  if (n >= 0){
    int cnt;
    for (cnt = 0; cnt < n; ++cnt) {
      puts (eps[cnt]->d_name);
      free (eps[cnt]);
    }
    free(eps);
  }  

  else{
    perror ("Couldn't open the directory");
  }
  return 0;
}

void send_file_list_2(){
  printf("\x1b[1m");
  print_dir(select_dir);
  printf("\x1b[0m");
  print_dir(select_not_dir);
}
