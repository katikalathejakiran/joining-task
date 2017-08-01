#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

#define error(m) {perror(m);return EXIT_FAILURE;}

int count;
char val;

void sigHandler(int sig){
FILE *fp;
  if ( (fp = fopen("configure.conf","r") ) == NULL ){
    error("fopen")
  }
  if ((fscanf(fp,"%c %d\n", &val, &count))){
    if(ferror(fp) ){
      error("fscanf")
    }
  }
}

int main(void){
  sigset_t sigmask;
  struct sigaction action;
  int i;

  printf("process PID:%d\n", getpid() );

  action.sa_handler = sigHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;
  sigaction(SIGHUP, &action, NULL);

  sigemptyset(&sigmask);
  sigaddset(&sigmask, SIGHUP);

  sigHandler(1);

  while (1){
  sleep(1);
  sigprocmask(SIG_BLOCK, &sigmask, NULL);

  for (i=0; i < count; i++){
    printf("%c",val);
  }
  sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
  printf("\n");

  }
  return EXIT_SUCCESS;
}
