#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> /////for struct sockaddr_in
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define DOMAIN AF_INET
#define TYPE SOCK_STREAM
#define SERVER_PORT 8000
#define PROTOCOL 0

int main(void) {
  int sock, fd, n;
  struct sockaddr_in server, client;
  char buffer[1024];
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
  while(1) {
    if( (fd=accept(sock, (struct sockaddr *)&client, (socklen_t *)&clientLen)) == -1) { //accept a connection form socket
      perror("fdaccept");
      printf("%d\n",errno);
      return EXIT_FAILURE;
    }


    printf("connected to client with port:%d and address:%d \n\n", client.sin_port, client.sin_addr.s_addr);

  /*************Talking to client**********/

    while ( (n=read(fd, buffer, 1024) ) > 0) {
      write(fd,buffer,n);
    }
    printf("disconnected client with port:%d and address: %d\n\n", client.sin_port, client.sin_addr.s_addr);

    close(fd);
  }
  return EXIT_SUCCESS;
}
