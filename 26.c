#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
  int i;


  for(i=1; i<31; i++){
    printf("%d\t%s\n", i, strsignal(i) );
  }

  return EXIT_SUCCESS;

}
