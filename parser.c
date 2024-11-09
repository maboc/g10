#include "parser.h"

struct dll * commands_free(struct dll * list){
  struct dll * tmp;
  
  list=dll_first(list);

  while(list->next!=NULL){
    tmp=list->next;
    free(list->payload);
    free(list);
    list=tmp;
  }
  free(list->payload);
  free(list);

  return NULL;
}

char * commands_get_part(struct dll * command, int gevraagd){
  int n=1;
  char * terug;
  
  command=dll_first(command);
  while(command->next!=NULL && n<gevraagd){
    command=command->next;
    n++;
  }

  if(n!=gevraagd){
    terug=NULL;
  } else {
    terug=command->payload;
  }
  return terug;
}


char * remove_leading_spaces(char * inp){
  char * no_leading_spaces;
  char * tmp;
  char * sp;
  
  tmp=malloc(strlen(inp)+1);
  bzero(tmp, strlen(inp)+1);
  tmp=strncpy(tmp, inp, strlen(inp));
  sp=tmp;
  
  while (strncmp(sp," ",1)==0) sp=sp+1;

  no_leading_spaces=malloc(strlen(sp)+1);
  bzero(no_leading_spaces, strlen(sp)+1);
  no_leading_spaces=strncpy(no_leading_spaces, sp, strlen(sp));

  free(tmp);
  
  return no_leading_spaces;
}

char * remove_trailing_spaces(char * inp){
  char * ep;
  char * tmp;
  
  ep=inp+strlen(inp)-1;

  while((strncmp(ep," ",1)==0) || (*ep=='\n') || (*ep=='\r')) ep=ep-1;

  tmp=malloc(ep-inp+2);
  bzero(tmp, ep-inp+2);

  tmp=strncpy(tmp, inp, ep-inp+1);

  return tmp;
}

char * remove_mid_spaces(char * inp){
  char * tmp; //result string
  char * p_tmp; //positional character
  char * p;
  int n;
  
  tmp=malloc(strlen(inp)+1);
  bzero(tmp, strlen(inp)+1);
  p_tmp=tmp;

  p=inp;
  n=0; //number of consecutive spaces (if bigger then one we do not need this space)
  while (p!=inp+strlen(inp)){
    if(strncmp(p, " ", 1)==0){
      n++;
    } else {
      n=0;
    }

    if(n<2){
      *p_tmp=*p;
      p_tmp=p_tmp+1;
    } 
      p=p+1;      
  }

  return tmp;
}

struct dll * parse(char * inpbuf){
  char * no_leading_spaces;
  char * no_trailing_spaces;
  char * no_mid_spaces;
  
  struct dll * parts=NULL;
  
  no_leading_spaces=remove_leading_spaces(inpbuf);
  free(inpbuf);
  no_trailing_spaces=remove_trailing_spaces(no_leading_spaces);
  free(no_leading_spaces);
  no_mid_spaces=remove_mid_spaces(no_trailing_spaces);
  free(no_trailing_spaces);

  
  // parts=dll_add(parts, no_mid_spaces);

  return parts;
}
