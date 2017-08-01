#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define error(msg) {perror(msg);return EXIT_FAILURE;}

int main(){
  pid_t parent, child;
  int status,p[2],i=0;
  char arg[100];
  char *p1, *array[2];

  parent = getpid();

  while(1){
    printf("theja>");

    scanf("%s",arg);

    p1 = strtok(arg,"|");

    while (p1 != NULL)
    {
        array[i++] = p1;

        p1 = strtok (NULL, "|");
    }

    for (i=0; i < 2; i++){
      printf("%s\n", array[i]);
    }


    if (-1 == pipe(p)){
      error("pipe");
    }

    if (-1 == (child = fork() ) ){
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


      execlp(array[1], array[1], NULL);

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

      execlp(array[0], array[0], NULL);

    }
  }
  return EXIT_SUCCESS;
}
