#include "handler.h"

void * handler(void * sck){
  int s = *(int *) sck;
  int proceed =0;//0 - proceed 1 - stop proceeding (quit)
  char * inpbuf;
  struct dll * commands=NULL;
  
  output_line(s, "Welcome G10\r\n");

  inpbuf=malloc(1000);
  while (proceed==0){
    bzero(inpbuf,1000);
    read(s, inpbuf,1000);

    commands=parse(inpbuf);
    
    if (strncmp(commands_get_part(commands,1), "quit", strlen("quit"))==0){
      proceed=1;
    }
    write(s, commands_get_part(commands,1), strlen(commands_get_part(commands,1)));
  }

  
  return NULL;
}
