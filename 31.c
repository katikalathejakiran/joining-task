#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alrmHandler(int sig){
printf("alarm triggered\n");
}

int main(void){
  struct sigaction action;
  char ch[100];
  int i;

  action.sa_handler = alrmHandler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  sigaction(SIGALRM, &action, NULL);

  while(1) {
    printf("String:");
    fflush(stdout);
    alarm(5);
    i= read(0, &ch, 100);
    alarm(0);
    if (-1 == i) {
      printf("  !!!time out!!!\n");
    }
    else {
    printf("input recieved:%s\n", ch);
    }

  }
}
