#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


#define error(msg) {perror(msg);return EXIT_FAILURE;}

int main(void){
  pid_t parent, child;
  int i;

  parent = getpid();


  if(-1 == (child = fork() ) ){
    error("child process:")
  }

  if (child){

    for (i = 0;i < 100; i++){
      printf("parent pid=%d, waiting for child=%d\n", parent, child);
    }
  }
  else {
    child = getpid();
    for (i = 0; i < 100; i++){
      printf("child pid=%d ,forked from parent=%d\n", child, parent);
    }
  }

  return EXIT_SUCCESS;
}
