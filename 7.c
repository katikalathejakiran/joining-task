#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define GENERATE 1

struct record{
  int id;
  char name[30];
};

struct record * toModify, data[3];

/*************************function for data generation*******************/

int dataGenerate(void){
  int fdWrite;

  data[0].id = 100;
  strcpy(data[0].name, "Theja");
  data[1].id = 131;
  strcpy(data[1].name, "Omkar");
  data[2].id = 141;
  strcpy(data[2].name, "Avinash");

  if (-1 == (fdWrite = open("test.txt", O_WRONLY | O_CREAT, 0744) ) ){
    perror("open test:");
    return EXIT_FAILURE;
  }

  if (-1 == (write(fdWrite, &data, sizeof(data) ) ) ){
    perror("open test:");
    return EXIT_FAILURE;
  }
return EXIT_SUCCESS;
}

/**************************************************************************/


/************************function to modify data **************************/
int dataModify(void){
  int fdWrite,n;
  char * records;

  if (-1 == ( fdWrite =  open("test.txt", O_RDWR | O_CREAT) ) ){
    perror("TEST:");
    return EXIT_FAILURE;
  }
  if ( -1 ==(n = lseek(fdWrite, 0, SEEK_END) ) ){
    perror("lseek:");
    return EXIT_FAILURE;
  }

  if ( (records = mmap(NULL, n, PROT_READ | PROT_WRITE, MAP_SHARED, fdWrite, 0) )== MAP_FAILED ){
    perror("MMAP:");
    return EXIT_FAILURE;
  }

  toModify = (struct record *)records;


  strcpy(toModify[1].name,"sunny");

  if (-1 == msync(toModify, n, MS_SYNC) ){
    perror("mysnc:");
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}
/******************************************************************/


int main(void){

/********control of dataGenerate and dataModify************/
  #if GENERATE
    if(-1 == dataGenerate() ){
      perror("dataGenerate():");
      return EXIT_FAILURE;
  }
  #else
    if(-1 == dataModify() ){
      perror("dataModify()");
      return EXIT_FAILURE;
  }
  #endif // GENERATE
/*********************************************************/

  return EXIT_SUCCESS;
}
