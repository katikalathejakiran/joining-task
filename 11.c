#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define error(msg) {perror(msg);\
                    return EXIT_FAILURE;}

int getFileSize(char * name){
 struct stat fInfo;
 if (-1 == stat(name, &fInfo)){
 error("stat");
 }
 printf("%ld\n", fInfo.st_size);
 return fInfo.st_size;

}

int main(void){
  DIR * directory;
  struct dirent *info;
  int size = 0;
  char path[100], direc[100];

  printf("enter path and directory:");
  scanf("%s %s",path,direc);

  if (-1 == chdir(path) ){
    error("chdir");
  }

  directory = opendir(direc);

  while ( (info = readdir(directory) ) != NULL){
    size += getFileSize(info->d_name);
    printf("%s ", info->d_name);
  }


  printf("\ntotal size:%d", size);

  if (-1 == closedir(directory) ){
    error("closedir");
  }
  return EXIT_SUCCESS;
}
