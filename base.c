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
  c=malloc(sizeof(struct control_struct));
  b->control=c;
  c->file=NULL;
  c->position=-1;
  c->status=0;
  
  if(bestaande_swid!=0) {
    b->swid=bestaande_swid;
    if (bestaande_swid>swid) swid=bestaande_swid;
    c->dirty=0;
    // If the base is read from by the reader from file, the control structure will be updated in the reader (not here)
  } else {
    b->swid=swid++;
    c->dirty=1;  // a base is always dirty as it is first created (not read from datafile)
  }
  
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
