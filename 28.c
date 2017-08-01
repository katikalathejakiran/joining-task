#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define error(m) {perror(m);return EXIT_FAILURE;}



void sigIntHandler(int sig){
  printf("interrupt handled\n");

}

int main(void){
  struct sigaction action;
  int Read, p[2];
  char buff[1000];

  action.sa_handler = sigIntHandler;
  sigemptyset(&action.sa_mask);

  action.sa_flags = 0;

  sigaction(SIGINT, &action, NULL);

  if (-1 == pipe(p) ){
    error("pipe");
  }

  while (1){
    if ( -1 == (Read = read(p[0], buff, 1000) ) ){
      //error("read p[o]");
    }
  printf("got %d number of bytes\n", Read, buff);

  }
  return EXIT_SUCCESS;
}
