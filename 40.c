#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> /////for struct sockaddr_in
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/select.h>
#include <string.h>

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
  int sock, fd, i;
  struct sockaddr_in server, client;
  char buf;
  socklen_t clientLen;
  fd_set fullClientList, activeClientList;


  FD_ZERO(&fullClientList);
  FD_ZERO(&activeClientList);
  printf("FD_SETSIZE = %d \n", FD_SETSIZE);

  /****Creating socket*********/
  sock = socket(DOMAIN, TYPE, PROTOCOL);
  printf("sock:%d\n",sock);


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
  FD_SET(sock, &fullClientList);


  while(1) {

    memcpy(&activeClientList, &fullClientList, sizeof(fullClientList));
    select(FD_SETSIZE, &activeClientList, NULL, NULL, NULL );

    if (FD_ISSET(sock, &activeClientList)) {
      clientLen = sizeof(client);
      if( (fd=accept(sock, (struct sockaddr *)&client, (socklen_t *)&clientLen)) == -1) { //accept a connection form socket
        perror("fdaccept");
        return EXIT_FAILURE;
      }
      FD_SET(fd,&fullClientList);
      printf("connected to client with port:%d and address:%d \n\n", client.sin_port, client.sin_addr.s_addr);
    }

    /*************Talking to client**********/
    for (i = 3 ;i < FD_SETSIZE; i++) {
      if (i != sock) {
        if(FD_ISSET(i, &activeClientList)) {
          if(read(i,&buf,1) < 1 ) {
            printf("Client closed connection, so server closing connection\n");
            close(i);
            FD_CLR(i, &fullClientList);}
            rotate(&buf);
          if (write(i,&buf,1) < 1) {
            printf("Client closed connection, so server closing connection\n");
            close(i);
            FD_CLR(i, &fullClientList);
          }
        }
      }
    }
  }
  return EXIT_SUCCESS;
}






