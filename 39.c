#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> /////for struct sockaddr_in
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>

#define ZOMBIE_SOLUTION 1
#define DOMAIN AF_INET
#define TYPE SOCK_STREAM
#define SERVER_PORT 8000
#define PROTOCOL 0

void rotate(char * data) {


  if (*data != '\r' && *data != '\n') {
      if (' ' == *data) {}
      if (*data >= 'a' && *data <= 'z'){
        if (*data  < 'n') {
          *data = *data +13;
        }
        else {
          *data = *data -13;
        }
      }
      if (*data >= 'A' && *data <= 'Z'){
        if (*data  < 'N') {
          *data = *data +13;
        }
        else {
          *data = *data -13;
        }
      }

  }
}


int main(void) {
  int sock, fd;
  struct sockaddr_in server, client;
  char buf;
  //char buffer[1024];
  socklen_t clientLen;
  /****Creating socket*********/
  sock = socket(DOMAIN, TYPE, PROTOCOL);


  /****Setting local address*******/
  server.sin_family = DOMAIN;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(SERVER_PORT);

  if(-1 ==  bind(sock, (struct sockaddr *)&server, sizeof(server) ) ) {
    perror("bind");
    return EXIT_FAILURE;
  } //assigning  a name to socket
  printf("server intialised on port %d: \n",SERVER_PORT);

  /******listening for connection*******/

  printf("listening...\n");
  if(-1 == listen(sock, 5) ) { //listen for connections on socket
    perror("listen");
    return EXIT_FAILURE;
  }

  clientLen = sizeof(client);

  while (1) {
    if( (fd=accept(sock, (struct sockaddr *)&client, (socklen_t *)&clientLen)) == -1) { //accept a connection form socket
      perror("fdaccept");
      printf("%d\n",errno);
      return EXIT_FAILURE;
    }
    #if (ZOMBIE_SOLUTION)
    signal(SIGCHLD, SIG_IGN);
    #endif // ZOMBIE_SOLUTION
    if ( fork() == 0) {
      close(sock);

      printf("connected to client with port:%d and address:%d \n\n", client.sin_port, client.sin_addr.s_addr);

    /*************Talking to client**********/

      while (read(fd,&buf,1) > 0) {
        rotate(&buf);
        write(fd,&buf,1);
      }

      printf("disconnected client with port:%d and address: %d\n\n", client.sin_port, client.sin_addr.s_addr);

      close(fd);

      exit(EXIT_SUCCESS);
    }
    else {
      close(fd);
    }
  }

  return EXIT_FAILURE;

}
