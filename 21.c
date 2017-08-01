#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define error(msg) {perror(msg);return EXIT_FAILURE;}

int main(void){
  pid_t parent, child;
  parent = getpid();
  int status;

  if(-1 == (child = fork() ) ){
  error("child process:")
  }

  if (child){

    printf("parent pid=%d\n",parent);
    waitpid(child, &status, 0);
    if (WIFEXITED(status)) {
      printf("child exited with status=%d\n", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status)) {
      printf("Child exited due to signal = %d\n", WTERMSIG(status));
    }
  }
  else{
    child=getpid();
    printf("child pid=%d\n", child);
    sleep(10);
    exit(3);
  }

  return EXIT_SUCCESS;
}
