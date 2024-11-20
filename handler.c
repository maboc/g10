#include "handler.h"

struct dll * results_free(struct dll * l){
  struct dll * tmp;
  
  if(l!=NULL){
    l=dll_first(l);
    while (l->next!=NULL){
      tmp=l->next;
      free(l);
      l=tmp;
    }
    free(l);
    l=NULL;
  }

  return l;
}

void write_prompt(int s){
  char * tmp;
  struct base_struct * active_base;

  tmp=malloc(10);
  bzero(tmp, 10);
  sprintf(tmp, "\r\n > ");
  write(s, tmp, strlen(tmp));

  free(tmp);
  
}

void * handler(void * sck){
  int s = *(int *) sck;
  int proceed =0;//0 - proceed 1 - stop proceeding (quit)
  char * inpbuf;
  struct dll * commands=NULL;
  struct base_struct * active_base=NULL;
  struct dll * results=NULL;
  
  output_line(s, "Welcome G10\r\n");

  write_prompt(s);
  
  while (proceed==0){
    inpbuf=malloc(1000);
    bzero(inpbuf,1000);
    read(s, inpbuf,1000);

    commands=parse(inpbuf);

    if (commands_count(commands)==1) {
      if (strncmp(commands_get_part(commands,1), "quit", strlen("quit"))==0){
	proceed=1;
      }
      if (strncmp(commands_get_part(commands,1), "shutdown", strlen("shutdown"))==0){
	proceed=1;
	goon=1;
      }
    } else if (commands_count(commands)==2) {
      if ((strncmp(commands_get_part(commands,1), "bases", 5)==0) && (strncmp(commands_get_part(commands,2), "list", 4)==0)){
	bases_list(s);
      } else if((strncmp(commands_get_part(commands,1), "use", 3)==0)){
	char * search;
	int isearch;

	search=malloc(strlen(commands_get_part(commands, 2))+1);
	bzero(search, strlen(commands_get_part(commands, 2))+1);
	search=strncpy(search, commands_get_part(commands, 2),strlen(commands_get_part(commands, 2)));

	isearch=atoi(search);

	active_base=bases_search_on_id(isearch);
	if(active_base!=NULL) base_list(s, active_base);
	
      } else if (((strncmp(commands_get_part(commands, 1), "node", 4)==0)) && (strncmp(commands_get_part(commands, 2), "add", 3)==0)) {
	if(active_base!=NULL){
	  struct node_struct * n=NULL;
	  n=node_new();
	  active_base->nodes=dll_add(active_base->nodes, n);
	  node_display(s, n);
	    
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
      } else if ((strncmp(commands_get_part(commands,1), "config", 6)==0) && (strncmp(commands_get_part(commands,2), "list", 4)==0)) {
	if (bases!=NULL){
	  struct base_struct * b;
	  b=bases_search_on_id(0);
	  base_display(s, b);
	}
      } else if ((strncmp(commands_get_part(commands, 1), "base", 4)==0) && (strncmp(commands_get_part(commands, 2), "display", 7)==0)) {
	if (active_base!=NULL){
	  base_display(s, active_base);
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
      }
    } else if (commands_count(commands)==4) {
      if ((strncmp(commands_get_part(commands,1), "node", 4)==0) && (strncmp(commands_get_part(commands,2), "search", 6)==0)){
	if (active_base!=NULL) {
	  results=nodes_search(active_base->nodes, commands_get_part(commands,3), commands_get_part(commands,4));
	  if (results!=NULL) nodes_display(s, results);
	  results=results_free(results);
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
      } 
    }
        
    commands=commands_free(commands);
    write_prompt(s);
  }
  
  close(s);
  pthread_exit(NULL);
}

