#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define error(msg) {perror(msg);return EXIT_FAILURE;}

int main(void){
  pid_t parent, child;

  if(-1 == (child = fork() ) ){
  error("child process:")
  }

  if (child){
    parent = getpid();
    printf("parent pid=%d\n",parent);
  }
  else{
    child=getpid();
    printf("child pid=%d\n", child);
  }

  return EXIT_SUCCESS;
}
