#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define GENERATE 1

struct record{
  int id;
  char name[30];
};

struct record toModify, data[3];

int main(void) {

  #if GENERATE
    int dataGenerate(void);
  #else
    int dataModify(void);
  #endif // GENERATE


  printf("size of data:%ld\n",sizeof(toModify));
  printf("size of data:%ld\n",sizeof(data));

  #if GENERATE
    if (-1 == dataGenerate() ){
      perror("dataGenerate:");
      return EXIT_FAILURE;
    }
  #else
    if (-1 == dataModify() ){
      perror("datModify:");
      return EXIT_FAILURE;
    }
  #endif // GENERATE

  return EXIT_SUCCESS;
}

int dataGenerate(void){
  int fdWrite;

  data[0].id = 100;
  strcpy(data[0].name,"Theja");
  data[1].id = 131;
  strcpy(data[1].name,"Omkar");
  data[2].id = 141;
  strcpy(data[2].name,"Avinash");

  if (-1 == (fdWrite = open("test.txt", O_WRONLY | O_CREAT) ) ){
    perror("open test:");
    return EXIT_FAILURE;
  }

  if (-1 == (write(fdWrite, &data, sizeof(data) ) ) ){
    perror("open test:");
    return EXIT_FAILURE;
  }
return EXIT_SUCCESS;
}

int dataModify(void){
  int fdWrite;
  int recordSize = sizeof(toModify);

  if (-1 == ( fdWrite =  open("test.txt", O_RDWR | O_CREAT) ) ){
    perror("TEST:");
    return EXIT_FAILURE;
  }
  if ( -1 == lseek(fdWrite, recordSize, SEEK_SET) ){
    perror("lseek:");
    return EXIT_FAILURE;
  }
  if ( -1 == read(fdWrite, &toModify, recordSize) ){
    perror("test:");
    return EXIT_FAILURE;
  }

  if (-1 == lseek(fdWrite, -1*recordSize, SEEK_CUR)){
    perror("lseek1:");
    return EXIT_FAILURE;
  }

  toModify.id=15566;
  strcpy(toModify.name, "kiran");

  if (-1 == write(fdWrite, &toModify, recordSize)){
    perror("testWrite:");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
