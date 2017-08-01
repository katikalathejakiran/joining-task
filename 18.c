#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>
#include <fcntl.h>

#define error(msg) {perror(msg);\
                    return EXIT_FAILURE;}

int main(void){
  struct tms info;
  clock_t startTime = clock();
  clock_t endTime;
  int i,fd;


  printf("sysconf:%ld\n",sysconf(_SC_CLK_TCK) );
  printf("clocks per second :%ld\n",CLOCKS_PER_SEC);

   /** Kill Time */
  fd=open("/dev/null", O_RDWR);
  for(i=0; i<100000000; i++) {
    if(write(fd, &i, sizeof(i)) == -1) {
      error("write");
    }
  }
  if(close(fd) == -1) {
    error("close");
  }

  if (-1 == times(&info) ){
    error("times()");
  }
  printf("User time:%ld\n", info.tms_cutime);
  printf("System time:%ld\n", info.tms_stime);
  printf("children user time:%ld\n",info.tms_cutime);
  printf("childres system time:%ld\n", info.tms_cstime);

  endTime=clock();
  printf("total time elapsed:%ld  final clock value:%ld", (startTime-endTime)/CLOCKS_PER_SEC, clock()/CLOCKS_PER_SEC);


  return EXIT_SUCCESS;
}
