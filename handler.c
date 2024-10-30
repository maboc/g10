#include "handler.h"

void * handler(void * sck){
  int s = *(int *) sck;
  int proceed =0;//0 - proceed 1 - stop proceeding (quit)
  char * inpbuf;
  
  output_line(s, "Welcome G10\r\n");

  inpbuf=malloc(1000);
  while (proceed==0){
    bzero(inpbuf,1000);
    read(s, inpbuf,1000);

    if (strncmp(inpbuf, "quit", 1000)==0){
      proceed=1;
    } else {
      write(s, inpbuf,1000);
    }
  }

  
  return NULL;
}
