#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define error(msg) {perror(msg);return EXIT_FAILURE;}

int main(void){
  pid_t child;
  int status;
  char cmd[20];

  while(1){
  printf("theja>");
  scanf("%s",cmd);
    if(-1 == (child = fork() ) ){
      error("child process:")
    }

    if (child){
      
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
      execlp(cmd, cmd, NULL);

      printf("Unknown command %s\n", cmd);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
