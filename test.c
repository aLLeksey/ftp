
#include<dirent.h>
#include<stdio.h>
#include<sys/stat.h>

void print_dir(const char * d);
int select_dir(struct dirent* a);
int select_not_dir(struct dirent* a);

int main(){
  //print_dir(".");
  //dir3();
  //print_dir2(select_dir);
  print_dir2(select_not_dir);
}

int select_dir(struct dirent* a){
  return is_directory(a->d_name);
}
int select_not_dir(struct dirent* a){
  return !select_dir(a);
}

    

void print_dir(const char * d){
     char buf[1000];
  DIR *dir;
  struct dirent *ent;
  if((dir = opendir(d)) != NULL ){
      while ((ent = readdir(dir)) != NULL){
        //TODO send ent->d_name
	printf("%s\n",ent->d_name);
      }
      closedir(d);
  }
}


static int
one (const struct dirent *unused)
{
  return 1;
}

int dir2()
{
  struct dirent **eps;
  int n;

  n = scandir ("./", &eps, one, alphasort);
  if (n >= 0)
    {
      int cnt;
      for (cnt = 0; cnt < n; ++cnt)
	{
	  puts (eps[cnt]->d_name);
	  free (eps[cnt]);
	}
      free(eps);
    }
  

  else
    perror ("Couldn't open the directory");

  return 0;
}


int is_directory(const char *path){
  struct stat stat_buf;
  if(stat(path, &stat_buf) != 0){
    return 0;
  }
  return S_ISDIR(stat_buf.st_mode);
}
int cmp_dir(struct dirent* a){
  return is_directory(a->d_name);
}

int dir3()
{
  struct dirent **eps_f;
  struct dirent **eps_dir;
  int n;

  n = scandir ("./", &eps_dir, cmp_dir, alphasort);
  if (n >= 0)
    {
      int cnt;
      for (cnt = 0; cnt < n; ++cnt)
	{
	  puts (eps_dir[cnt]->d_name);
	  free (eps_dir[cnt]);
	}
      free(eps_dir);
    }
  

  else
    perror ("Couldn't open the directory");

  return 0;
}

int print_dir2(int (*filter)(const struct dirent *))
{
  struct dirent **eps;
  int n;

  n = scandir ("./", &eps, filter, alphasort);
  if (n >= 0)
    {
      int cnt;
      for (cnt = 0; cnt < n; ++cnt)
	{
	  puts (eps[cnt]->d_name);
	  free (eps[cnt]);
	}
      free(eps);
    }
  

  else
    perror ("Couldn't open the directory");

  return 0;
}

// cmp without case
// instead of alpha;
int cmp_dir2(struct dirent* a, struct dirent* b){
  // to cmp without case
  // need allockate memeory and to_lower for each letter
  // ...
}



