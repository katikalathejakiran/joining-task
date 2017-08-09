#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define DOMAIN AF_INET
#define BUFF_SIZE 1024
#define TYPE SOCK_DGRAM
#define PROTOCOL 0
#define ERROR(msg) { perror(msg);exit(EXIT_FAILURE);}
#define PORT 8010

int main(void) {
  int sock, count, yes=1;
  struct sockaddr_in server, client;
  char buff[BUFF_SIZE];
  socklen_t clientSize;
  //pid_t childPid;

  /*****creating server socket**********/
  if( (sock = socket(DOMAIN, TYPE, PROTOCOL) ) == -1) {
    ERROR("socket");
  }
  if( (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof( yes) ) ) == -1) {
    ERROR("setsockopt-SO_BROADCAST");
  }
  if( (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (char *)&yes, sizeof( yes) ) ) == -1) {
    ERROR("setsockopt-SO_REUSEPORT");
  }


  /***socket binding*****/
  server.sin_family = DOMAIN;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  /*****binding the port******/


  if(bind(sock, (struct sockaddr *)&server, sizeof(server) ) == -1 ) {
    ERROR("bind");
  }

  clientSize = sizeof(client);

  if((fork()) == 0){     /*******child process client*****/
    while(1) {
      if ( (count = recvfrom(sock,buff,BUFF_SIZE, 0, (struct sockaddr *)&client, (socklen_t *)&clientSize ) )== -1) {
        ERROR("recvfrom");
      }

      if (write(1,buff, count) == -1) {
          ERROR("write into buff");
        }
        //exit(0);
    }
  }
  else {              /****parent process server****/
    while (1) {
      if( (count = read(0, buff, BUFF_SIZE) ) == -1) {
        ERROR("read from stdout");
      }

      /***broadcast data****/

      server.sin_addr.s_addr = 0xFFFFFFFF;

      if(sendto(sock, buff, count, 0, (struct sockaddr *)&server, sizeof(server)) == -1) {
        ERROR("sendto");
      }

    }
  }

return EXIT_SUCCESS;
}

