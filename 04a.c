#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>


int main(void) {
    int blocksize;
    long int blockcount;
    FILE *file;
    double time_spent;
    clock_t begin,end;
    void *buff;
    
    printf("enter block size and block count:");
    scanf("%d %ld", &blocksize, &blockcount);
    
    buff = calloc(blocksize,sizeof(char));
   

    file = fopen("test.txt","w");

    if(file == NULL){
      perror("Error in opening file");
      return EXIT_FAILURE;
    }

    begin = clock();

    while(blockcount){
      fwrite(buff, 1, blocksize, file);
      blockcount--;
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
    printf("Execution Time:%f\n",time_spent);
    
    return EXIT_SUCCESS;

}
