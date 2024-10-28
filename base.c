#include "base.h"

struct base_struct * base_new(){
  struct base_struct * b;

  b=malloc(sizeof(struct base_struct));
  b->swid=swid++;
  b->attributes=NULL;
  b->nodes=NULL;

  return b;
}

void base_display(struct base_struct * base){
  struct dll * l;
  if (base!=NULL){
    printf("=== Base ===\n");
    printf("SWID : %i\n", base->swid);

    l=base->attributes;
    attributes_display(l);
    
    l=base->nodes;
    nodes_display(l);
    
  }
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
