#include "handler.h"

void * handler(void * sck){
  int s = *(int *) sck;
  int proceed =0;//0 - proceed 1 - stop proceeding (quit)
  char * inpbuf;
  struct dll * commands=NULL;
  
  output_line(s, "Welcome G10\r\n");


  while (proceed==0){
    inpbuf=malloc(1000);
    bzero(inpbuf,1000);
    read(s, inpbuf,1000);

    commands=parse(inpbuf);
    
    if (strncmp(commands_get_part(commands,1), "quit", strlen("quit"))==0){
      proceed=1;
    }
    if (strncmp(commands_get_part(commands,1), "shutdown", strlen("shutdown"))==0){
      proceed=1;
      goon=1;
    }
    write(s, commands_get_part(commands,1), strlen(commands_get_part(commands,1)));

    //    free(inpbuf);
    commands=commands_free(commands);
  }

  close(s);
  pthread_exit(NULL);
}
