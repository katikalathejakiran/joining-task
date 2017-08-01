#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  time_t datetime;
  struct tm *lt;
  char buff[1000];

  datetime = time(NULL);

  if(!datetime){
    perror("time()");
    return EXIT_FAILURE;
  }

  lt = localtime(&datetime);
  strftime(buff, 1000, "%A %B %C", lt);

  printf("ctime:%s", ctime(&datetime) );
  printf("strftime:%s", buff);

  return EXIT_SUCCESS;


}
