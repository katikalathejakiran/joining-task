#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>

#define error(msg) {perror(msg); exit(EXIT_FAILURE);}

int main(void) {
  int inotifyFd;
  int watchDescriptor;
  FILE *conf;
  struct inotify_event *event;

  char buff[sizeof( struct inotify_event)];

  if (-1 == (inotifyFd = inotify_init() ) ) {
    error("inotifyFd");
  }


  if(-1 == (watchDescriptor = (inotify_add_watch(inotifyFd, "config.conf", IN_DELETE_SELF | IN_MODIFY) ) ) ) {
    error("watchDescriptor");
  }
int n;
  while (1) {
  printf("enter into loop\n");
    if (-1 ==(n = read(inotifyFd,buff,sizeof(buff) ) ) ) {
      error("read");
    }
  printf("read: %d,buff: %s", n, buff);


    event = (struct inotify_event *)buff;

    if ((*event).mask & IN_MODIFY) {
     printf("got event on file modified %d \n",(*event).wd);
    }
    if ((*event).mask & IN_DELETE_SELF) {
      printf("got event on file deleted %d \n",(*event).wd);
    }
  }
  return EXIT_SUCCESS;
}
