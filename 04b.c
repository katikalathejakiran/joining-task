#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#define PERMISSION 0744
#define MODE O_RDWR | O_CREAT

int main(){
  int fd,blocksize;
  long int blockcount;
  double time_spent;
  printf("Enter blockSize and blockcount:");
  scanf("%d %ld", &blocksize, &blockcount);
  void * buff=malloc(blocksize*sizeof(char));

  fd = open("test.txt", MODE, PERMISSION);

  if (fd < 0){
    perror("Error!!!");
    return EXIT_FAILURE;
  }

  clock_t begin = clock();

  while (blockcount){
    write(fd,buff,blocksize);
    blockcount--;
  }

  clock_t end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Executable Time(low level i/o) : %f",time_spent);

  return EXIT_SUCCESS;
}
