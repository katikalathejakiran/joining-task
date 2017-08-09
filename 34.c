/**Write a client program that connects to the rot13 server (update /etc/services file so
that the getservbyname() can be called) and open two instances of the client to fiddle with
concurrent connections. You should see that one client is blocked until one client terminates its
connection*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>   //socket()
#include <sys/socket.h> //socket()
#include <netdb.h>   //getservbyname()
#include <unistd.h>  //read()
#include <string.h>


#define DOMAIN AF_INET
#define TYPE SOCK_STREAM
#define PROTOCOL 0
#define BUFFERSIZE 1024
#define ERROR(msg) {perror(msg);exit(EXIT_FAILURE);}

int main() {
  int sock, n;
  char buffer[1024];
  struct sockaddr_in server;
  struct servent *serverInfo;
  struct hostent *hostInfo;

  /************create socket*********/
  sock = socket(DOMAIN, TYPE, PROTOCOL);


  /******getting port number from /etc/services  ***********/
  serverInfo = getservbyname("rot13","tcp");
  hostInfo = gethostbyname("localhost");

  /***********setting local address*******/
  server.sin_family = DOMAIN;
  memcpy(&server.sin_addr, hostInfo->h_addr, hostInfo->h_length);
  //server.sin_addr.s_addr = hostInfo->h_addr[0];
  server.sin_port = serverInfo->s_port;

  /*****writing and reading the data******/
  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == -1) {
    ERROR("connect");
  }

  printf("connected to server with port %d and address %d \n", server.sin_port, server.sin_addr.s_addr);


  while (1) {

    if ( (n = read(0,buffer, BUFFERSIZE) ) == -1) {
      ERROR("stdin");
    }
    //fflush(stdout);
    if (write(sock,buffer,n) == -1) {
      ERROR("write req");
    }
    if (read(sock,buffer,n) == -1) {
      ERROR("read data");
    }
    //fflush(stdout);

    if (write(1,buffer,n) == -1) {
      ERROR("stdout");
    }

    //memset(&buffer,0,n);
}

  return EXIT_SUCCESS;
}
