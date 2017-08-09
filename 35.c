/**Modify the program #34 that connects to the rot13 server by using the modern way of
populating the server details using the getaddinfo() system call. Make sure the code is
completely protocol agnostic such that if the rot13 server changes from IPv4 to IPv6, the client
is able to connect to it*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>   //socket()
#include <sys/socket.h> //socket()
#include <netdb.h>   //getservbyname()
#include <unistd.h>  //read()
#include <string.h>


#define DOMAIN AF_UNSPEC
#define TYPE SOCK_STREAM
#define PROTOCOL 0
#define BUFFERSIZE 1024
#define ERROR(msg) {perror(msg);exit(EXIT_FAILURE);}

int main(void) {
  int sock, n, success = 0;
  char buffer[1024];

  struct addrinfo hints;
  struct addrinfo *result;



  memset(&hints, 0, sizeof(struct addrinfo) );
  hints.ai_family = DOMAIN;
  hints.ai_socktype = TYPE;
  hints.ai_protocol = PROTOCOL;

  if (getaddrinfo("::1", "rot13", &hints, &result) != 0) {
    ERROR("getaddrinfo");
  }

  while (result != NULL) {
    /************create socket*********/
    if(-1 == (sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol ) ) ) {
      ERROR("sock");
    }



    /*****creating connection******/
    if (connect(sock, (struct sockaddr *)result->ai_addr, result->ai_addrlen) == 0) {
      success = 1;
      result = NULL;
    }
    else {
      printf("unable to create socket, moving to next \n");
      result=result->ai_next;
    }

    if (success == 0){
      printf("unable to connect to server\n");
      return EXIT_FAILURE;
    }


    freeaddrinfo(result);

  }


  while (1) {

    if ( (n = read(0,buffer, BUFFERSIZE) ) == -1) {
      ERROR("stdin");
    }

    if (write(sock,buffer,n) == -1) {
      ERROR("write req");
    }

    sleep(2);

    if (read(sock,buffer,n) == -1) {
      ERROR("read data");
    }


    if (write(1,buffer,n) == -1) {
      ERROR("stdout");
    }


}

  return EXIT_SUCCESS;

}
