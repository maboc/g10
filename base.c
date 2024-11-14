#include "base.h"

void base_list(int s, struct base_struct * b){
  char * tmp;

  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "--- Base ---\r\n");
  write(s, tmp, strlen(tmp));
  bzero(tmp, 100);
  sprintf(tmp, "SWID : %i\r\n", b->swid);
  write(s, tmp, strlen(tmp));
  bzero(tmp, 100);
  sprintf(tmp, "Nodes : %i\r\n", nodes_count(b->nodes));
  write(s, tmp, strlen(tmp));
  free(tmp);
  attributes_list(s, b->attributes);
}

struct base_struct * base_new(){
  struct base_struct * b;

  b=malloc(sizeof(struct base_struct));
  b->swid=swid++;
  b->attributes=NULL;
  b->nodes=NULL;

  return b;
}

void base_display(int s, struct base_struct * b){
  char * tmp;
  
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "--- Base ---\r\n");
  write(s, tmp, strlen(tmp));
  bzero(tmp, 100);
  sprintf(tmp, "SWID : %i\r\n", b->swid);
  write(s, tmp, strlen(tmp));
  bzero(tmp, 100);
  sprintf(tmp, "Nodes : %i\r\n", nodes_count(b->nodes));
  write(s, tmp, strlen(tmp));
  free(tmp);
  attributes_list(s, b->attributes);
}

struct base_struct * base_search_by_swid(long int swid){
  struct base_struct * tmp;
  struct base_struct * b=NULL;
  struct dll * bs;
  int gevonden=0;

  bs=bases;
  
  if (bs!=NULL){
    bs=dll_first(bs);
    while(bs->next!=NULL && gevonden==0){
      tmp=bs->payload;
      if (tmp->swid==swid){
	b=tmp;
	gevonden=1;
      }
      bs=bs->next;
    }
    tmp=bs->payload; 
    if (tmp->swid==swid)
      b=tmp;
  }
  return b;
}
