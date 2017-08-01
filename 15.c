#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

extern char * optarg;
extern int optind, opterr, optopt;

int main(int argc ,char * argv[] ){
  char opt;
  int cflag = 0, vflag = 0,bflag = 0,fflag = 0, bopt = 0;
  char *fopt;
  int i,j;

  while ( (opt=getopt(argc, argv,"cvb:f:") ) != -1) {
    switch (opt) {
      case 'c': cflag = 1;
                break;
      case 'b': bflag = 1;
                bopt = atoi(optarg);
                break;
      case 'v': vflag = 1;
                break;
      case 'f': fflag =1;
                fopt=optarg;
                break;
      default : printf("usage: c v -b <num> -f <text> \n");

    }
  }
  if(cflag) {
    printf("found option \n");
  }
  if(vflag) {
    printf("found option \n");
  }
  if(bflag) {
    printf("found option and value is %d \n",bopt);
  }
  if(fflag) {
    printf("found option and value is %s \n",fopt);
  }



  i = optind;
  j = argc-optind;

  while (j) {
    printf("found non option arg:%s\n",argv[i]);
    i++;
    j--;
  }

  return EXIT_SUCCESS;
}
