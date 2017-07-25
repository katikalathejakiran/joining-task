#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
    int fd,fd1;
    char buff[1024];
    fd1 = open("bar", O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    fd = open("foo", O_RDONLY, S_IRWXG | S_IRWXU);

    if (fd1==-1){
        perror("ERROR IN OPENING bar:\n");
        return 1;
    }

    if (fd<0){
        perror("ERROR in READING foo:\n");
        return 1;
    }

    while (read(fd, buff, 1) > 0){
        if (write(fd1, buff, 1) == -1){
            perror("Error in writing bar");
            return 1;
        }
    }
    return 0;
}
