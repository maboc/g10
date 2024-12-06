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

struct base_struct * base_new(long int bestaande_swid){
  struct base_struct * b;
  struct control_struct * c;

  b=malloc(sizeof(struct base_struct));
  if(bestaande_swid!=0) {
    b->swid=bestaande_swid;
    if (b->swid>swid) swid=b->swid;
  } else {
    b->swid=swid++;
  }
  b->attributes=NULL;
  b->nodes=NULL;
  c=malloc(sizeof(struct control_struct));
  if(bestaande_swid!=0) {
    c->dirty=0;
  } else {
    c->dirty=1;  // a base is always dirty as it is first created
  }
  c->file=NULL;
  c->position=-1;
  b->control=c;
  
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
  nodes_display(s, b->nodes);
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

struct base_struct * base_search_by_kv(char * key, char * value){
  struct base_struct * tmp, * tmp2;
  struct base_struct * b=NULL;
  struct dll * bs;
  int gevonden=0;

  bs=bases;
  
  if (bs!=NULL){
    bs=dll_first(bs);
    while(bs->next!=NULL && gevonden==0) {
      tmp=bs->payload;
      if (attribute_exists_by_kv(tmp->attributes, "name", "files")==1) {
	gevonden=1;
	b=tmp;
      }
      
      bs=bs->next;
    }
    tmp=bs->payload; 
    if (attribute_exists_by_kv(tmp->attributes, "name", "files")==1) b=tmp;
  }
  return b;
  
}
