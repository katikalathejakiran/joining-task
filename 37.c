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
#define TYPE SOCK_DGRAM
#define PROTOCOL 0
#define BUFFERSIZE 516
#define ERROR(msg) {perror(msg);exit(EXIT_FAILURE);}


void tftp_read(int sock, struct sockaddr * server, socklen_t serverLen, char *file) {
  char buffer[BUFFERSIZE];
  short opcode, blockNumber;
  char *p =buffer;
  int payloadLength;
  struct sockaddr_in serverResp;
  int count;
  socklen_t serverRespLen;

  opcode = htons(1);     //Read request
  memcpy(p, &opcode, sizeof(short));
  p = p+2;
  p = strcpy(p,file);
  p = p + strlen(file) +1;
  p = strcpy(p,"octet");
  p = p + strlen("octet") + 1;    //mode declaration
  payloadLength = p-buffer;       //calculation of paylength


  if((sendto(sock, buffer, payloadLength, 0, server, serverLen)) == -1) {
    ERROR("sendto");
  }

  do {
    serverRespLen = sizeof(struct sockaddr_in);
    /******handle data and error*******/
    if( (count = recvfrom(sock, buffer, BUFFERSIZE, 0, (struct sockaddr *)&serverResp, &serverRespLen) ) == -1) {
      ERROR("recvfrom");
    }

    memcpy(&opcode, buffer, sizeof(short));
    memcpy(&blockNumber, buffer, sizeof(short));
    opcode = ntohs(opcode);
    blockNumber = ntohs(blockNumber);


    switch(opcode) {
      case 5: ERROR("tftp error code");       //error opcode
              break;
      case 3:                                   // data opcode
              if ( write(1, buffer + 4, count -4) == -1) {
                ERROR("write");
              }
              /***send acknowledge*****/
              opcode = htons(4);        //ack opcode

              memcpy(buffer, &opcode, sizeof(short));
              payloadLength = 4;

              if ( (sendto(sock, buffer, payloadLength, 0, (struct sockaddr *)&serverResp, sizeof(struct sockaddr_in) ) ) == -1) {
                  ERROR("sendto ack");
                }
                break;
      default:
              fprintf(stderr, "unknown opcode from server\n");
              break;

    }
  }while (count == 516);
}


int main(void) {
  int sock, success = 0;
  char filename[]="foo";
  struct addrinfo hints;
  struct addrinfo *result, *temp;



  memset(&hints, 0, sizeof(struct addrinfo) );
  hints.ai_family = DOMAIN;
  hints.ai_socktype = TYPE;
  hints.ai_protocol = PROTOCOL;

  if (getaddrinfo("127.0.0.1", "tftp", &hints, &result) != 0) {
    ERROR("getaddrinfo");
  }

  while (result != NULL) {
    /************create socket*********/
    if( (sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol ) ) != -1 ) {
      printf("connection established... \n");
      success = 1;
      temp = result;
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



  }

tftp_read(sock, temp->ai_addr, temp->ai_addrlen, filename);


  freeaddrinfo(result);
  close(sock);
  return EXIT_SUCCESS;

}
