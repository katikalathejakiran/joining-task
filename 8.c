#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(void) {
  char fileName[20];

  void modifiedDetails(char *);

  printf("enter name of file:");
  scanf("%s",fileName);

  modifiedDetails(fileName);
  return EXIT_SUCCESS;
}
/****************function to print modified details of file ******************************/
void modifiedDetails(char *name) {
  struct stat info;

  stat(name,&info);

  printf("last accessed: %s", ctime(&info.st_atime));
  printf("last modified: %s", ctime(&info.st_mtime));
  printf("last changed: %s", ctime(&info.st_ctime));

}
/*****************************************************************************************/
