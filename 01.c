#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void){
    int fd;
    fd = open("test.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd < 0){
        printf("error no in open test.text:%d",errno);
        perror("ERROR OCCURED in opening test.txt\n");
        return EXIT_FAILURE;
    }
    if (write(fd, "\nHELLO WORLD\n", 13) < 0){
        printf("error no in write:%d", errno);
        perror("ERROR occured in writing test.txt\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
