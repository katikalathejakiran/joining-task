#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void){
  char fileName[20];
  void details(char *);

  printf("enter file name:");
  scanf("%s",fileName);

  details(fileName);

  return EXIT_SUCCESS;
}
/******************************functionality of ls -l command ***********************************/
void details(char *name) {
  struct stat info;
  char type,permission[9];
  off_t size;

  stat(name,&info);

  if ( S_ISREG(info.st_mode) ) {
    type = '-';
  }
  else if (S_ISDIR(info.st_mode)) {
    type = 'd';
  }
  else if (S_ISCHR(info.st_mode)) {
    type = 'c';
  }
  else if (S_ISBLK(info.st_mode)) {
    type = 'b';
  }
  else if (S_ISLNK(info.st_mode)) {
    type = 'l';
  }
  else if (S_ISSOCK(info.st_mode)) {
    type = 's';
  }

  permission[0] = (info.st_mode & S_IRUSR) ? 'r' : '-';
  permission[1] = (info.st_mode & S_IWUSR) ? 'w' : '-';
  permission[2] = (info.st_mode & S_IXUSR) ? 'x' : '-';
  permission[3] = (info.st_mode & S_IRGRP) ? 'r' : '-';
  permission[4] = (info.st_mode & S_IWGRP) ? 'w' : '-';
  permission[5] = (info.st_mode & S_IXGRP) ? 'x' : '-';
  permission[6] = (info.st_mode & S_IROTH) ? 'r' : '-';
  permission[7] = (info.st_mode & S_IWOTH) ? 'w' : '-';
  permission[8] = (info.st_mode & S_IXOTH) ? 'x' : '-';

  size=info.st_size;

  printf("%c%s %ld\n",type,permission,size);


}
/**********************************************************************************/
