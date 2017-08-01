#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int printDetails(char * name){
  struct stat fileInfo;
  char r;

  if(stat(name, &fileInfo) == -1) {
    perror("stat");
    return EXIT_FAILURE;
  }

  if(S_ISREG(fileInfo.st_mode)) { r = '-'; }
  if(S_ISDIR(fileInfo.st_mode)) { r = 'd'; }
  if(S_ISCHR(fileInfo.st_mode)) { r = 'c'; }
  if(S_ISBLK(fileInfo.st_mode)) { r = 'b'; }
  if(S_ISFIFO(fileInfo.st_mode)) { r = 'p'; }
  if(S_ISLNK(fileInfo.st_mode)) { r = 'l'; }
  if(S_ISSOCK(fileInfo.st_mode)) { r = 's'; }

  printf("%c%c%c%c%c%c%c%c%c%c  ", r,
         (fileInfo.st_mode & S_IRUSR)? 'r' : '-',
         (fileInfo.st_mode & S_IWUSR)? 'w' : '-',
         (fileInfo.st_mode & S_IXUSR)? 'x' : '-',
         (fileInfo.st_mode & S_IRGRP)? 'r' : '-',
         (fileInfo.st_mode & S_IWGRP)? 'w' : '-',
         (fileInfo.st_mode & S_IXGRP)? 'x' : '-',
         (fileInfo.st_mode & S_IROTH)? 'r' : '-',
         (fileInfo.st_mode & S_IWOTH)? 'w' : '-',
         (fileInfo.st_mode & S_IXOTH)? 'x' : '-');

  printf(" %8ld \n",fileInfo.st_size);

return EXIT_SUCCESS;
}

int main(void){
  DIR * directory;
  struct dirent *info;
  char path[1000],direc[100];

  printf("enter path and directory name:");
  scanf("%s %s",path,direc);

  if (-1 == chdir(path)){
    perror("chdir");
    return EXIT_FAILURE;
  }
  if ( (directory=opendir(direc) ) == NULL ){
    perror("opendir");
    return EXIT_FAILURE;
  }

  while ( (info = readdir(directory) ) != NULL){
    printDetails(info->d_name);
  }
  if (-1 == closedir(directory)){
    perror("closedir:");
    return EXIT_FAILURE;
  }


}
