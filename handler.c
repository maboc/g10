#include "handler.h"

void write_prompt(int s){
  char * tmp;

  tmp=malloc(10);
  bzero(tmp, 10);
  sprintf(tmp, "\n\n > ");
  write(s, tmp, strlen(tmp));

  free(tmp);
  
}

void * handler(void * sck){
  int s = *(int *) sck;
  int proceed =0;//0 - proceed 1 - stop proceeding (quit)
  char * inpbuf;
  struct dll * commands=NULL;
  
  output_line(s, "Welcome G10\r\n");

  write_prompt(s);
  
  while (proceed==0){
    inpbuf=malloc(1000);
    bzero(inpbuf,1000);
    read(s, inpbuf,1000);

    commands=parse(inpbuf);
    
    if (strncmp(commands_get_part(commands,1), "quit", strlen("quit"))==0){
      proceed=1;
    } else if (strncmp(commands_get_part(commands,1), "shutdown", strlen("shutdown"))==0){
      proceed=1;
      goon=1;
    } 

    if (strncmp(commands_get_part(commands,1), "bases", strlen("bases"))==0){
      if(strncmp(commands_get_part(commands,2), "list", strlen("list"))==0){
	bases_list(s);
      }
    }

    commands=commands_free(commands);
    write_prompt(s);

  }

  close(s);
  pthread_exit(NULL);
}
