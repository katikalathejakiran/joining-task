#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void){
    FILE *fp , *fp1;
    char c;

    if ( (fp = fopen("foo", "r") )== NULL){
        perror("error in opening foo\n");
        return EXIT_FAILURE;
    }

    if ( (fp1 = fopen("bar", "w") ) == NULL){
        perror("error in opening bar\n");
        return EXIT_FAILURE;
    }

    while( (c=fgetc(fp) ) != EOF){
        fputc(c,fp1);
    }

    fclose(fp1);
    fclose(fp);
    return EXIT_SUCCESS;
}
