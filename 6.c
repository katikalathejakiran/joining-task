#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(void){
  int fdRead,fdWrite;
  char *Read,*Write;
  size_t n;

  if ( (fdRead = open("foo.txt", O_RDONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IRUSR) ) < 0){
    perror("open foo:");
    return EXIT_FAILURE;
  }
  if ( (fdWrite = open("bar.txt",O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IRUSR) ) < 0){
    perror("open bar:");
    return EXIT_FAILURE;
  }

  n = lseek(fdRead,0,SEEK_END);

  ftruncate(fdWrite, n);  // to make equal size of memorie for mapping

  Read = mmap(NULL, n, PROT_READ, MAP_SHARED, fdRead, 0);
  Write = mmap(NULL, n, PROT_WRITE | PROT_READ, MAP_SHARED, fdWrite, 0);

  memcpy(Write,Read,n);   // copying from write memory to read memory

  msync(Write,n,MS_SYNC); // flushing content from memory to filr

  return EXIT_SUCCESS;
}
