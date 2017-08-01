#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define error(msg) {perror(msg);return EXIT_FAILURE;}

int main(void){
  pid_t parent, child;
  parent = getpid();
  int status,p[2];

  if (-1 == pipe(p)){
    error("pipe");
  }

  if(-1 == (child = fork() ) ){
  error("child process")
  }

  if (child){
    if(-1 == dup2(p[0],0) ){
      error("dup2 of p[0]");
    }

    if(-1 == close(p[1]) ){
      error("close p[1]");
    }

    printf("parent pid=%d\n",parent);


    execlp("sort", "sort", "-r", NULL);

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

    if (-1 == dup2(p[1], 1) ){
      error("dup2 p[1] in child");
    }

    if (-1 == close(p[0]) ){
      error("close p[0] in child");
    }

    execlp("ls", "ls", NULL);

  }

  return EXIT_SUCCESS;
}
