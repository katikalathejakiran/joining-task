#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define error(msg) {perror(msg);return EXIT_FAILURE;}

int main(void){
  pid_t parent, child;
  parent = getpid();
  int status,i;
  char *cmd[]={"ps", "ls", "date", "goof"};

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
    printf("1. ps\t2. ls\t3. date\t4. goof\n");

    scanf("%d", &i);


    if(i > 0 && i < 5) {
      printf("Found command %s\n", cmd[i-1]);
      execlp(cmd[i-1], cmd[i-1], NULL);
    }
    else{
      printf("Unknown command option %d\n", i);
      return EXIT_FAILURE;
    }

  }

  return EXIT_SUCCESS;
}
