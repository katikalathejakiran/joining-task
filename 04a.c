#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>


int main(void){
    int blocksize;
    long int blockcount;
    FILE *file;
    printf("enter block size and block count:");
    scanf("%d %ld", &blocksize, &blockcount);
    void *buff = calloc(blocksize,sizeof(char));
    double time_spent;

    file = fopen("test.txt","w");

    if(file == NULL){
      perror("Error in opening file");
      return EXIT_FAILURE;
    }

    clock_t begin = clock();

    while(blockcount){
      fwrite(buff, 1, blocksize, file);
      blockcount--;
    }

    clock_t end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Execution Time:%f\n",time_spent);
    return EXIT_SUCCESS;

}
