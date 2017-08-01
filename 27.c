#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int counter;

void sigHandler(int sig){
  counter = 0;
}

int main(void){
  sigset_t sigmask;
  struct sigaction action;

  printf("parent:%d \n", getpid() );

  action.sa_handler = sigHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;

  sigaction(SIGINT, &action, NULL);

  action.sa_handler = SIG_IGN;

  sigaction(SIGQUIT, &action, NULL);
  sigaction(SIGTERM, &action, NULL);

  sigemptyset(&sigmask);
  sigaddset(&sigmask , SIGINT);

  while (1) {
    sleep(1);
    printf("count:%d \n",counter);
    sigprocmask(SIG_BLOCK, &sigmask, NULL);
    counter++;
    sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
  }


  return EXIT_SUCCESS;
}
