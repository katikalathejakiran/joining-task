#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
  int i;

  for(i = 1;i < argc; i++){
  printf("%s\t", argv[i] );
  }

  printf("\n");
  printf("%d", argc);

  return EXIT_SUCCESS;

}
