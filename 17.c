#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define ERROR(msg) {perror(msg);\
                    exit(EXIT_FAILURE);}

void path_dir_lookup(char *);

int histogram[24];

int main(void) {
  char path[PATH_MAX];//="/home/katikalathejakiran/Workspace/1-8-17";
  int i=0;

  //getcwd(path,PATH_MAX);
  printf("enter the path:");
  scanf("%s",path);
  path_dir_lookup(path);

  while(i<24) {
    printf("%d %d\n",i,histogram[i]);
    i++;
  }
}

void path_dir_lookup(char *dname) {

  struct stat sb;
  struct tm *modtime;
  DIR *dirp;
  struct dirent *direntp;
  char path[PATH_MAX];


  if( (dirp=opendir(dname)) == NULL) {
    ERROR("open dir");
  }
  while((direntp=readdir(dirp))!= NULL) {
    strcpy(path, dname);
    strcat(path, "/");
    strcat(path, direntp->d_name);
      if(stat(path, &sb) == -1) {
        ERROR("stat");
      }
      if(S_ISDIR(sb.st_mode)) {

      if(path[strlen(path)-1] != '.') {
        printf("path: %s \n",path);

        path_dir_lookup(path); }
      } else {
        modtime = localtime(&sb.st_mtime);
        printf(" %s:",direntp->d_name);
        printf(" %d \n", modtime->tm_hour);

        histogram[modtime->tm_hour]++;
        }
  }
  if(closedir(dirp) == -1) {
    ERROR("closedir");
  }

}
