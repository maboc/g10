#include "relation.h"

struct relation_struct * relation_search_by_swid(struct node_struct * n, int i){
  struct relation_struct * r=NULL, * rtmp=NULL;
  struct dll * list;
  int gevonden=0;

  list=n->relations;
  if (list!=NULL) {
    list=dll_first(list);
    while((list->next!=NULL) &&(gevonden==0)){
      rtmp=list->payload;
      if(rtmp->swid==i) {
	gevonden=1;
	r=rtmp;
      }
      list=list->next;
    }
    rtmp=list->payload;
    if(rtmp->swid==i) {
      gevonden=1;
      r=rtmp;
    }
  }

  return r;
}

struct relation_struct * relation_new(struct node_struct * n){
  struct relation_struct * r;

  r=malloc(sizeof(struct relation_struct));
  r->swid=swid++;
  r->node_to=n;
  r->attributes=NULL;

  return r;
}

void relation_display(int s, struct relation_struct * r){
  char * tmp;

  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp,"--- Relation ---\r\n");
  write(s, tmp, strlen(tmp));
  bzero(tmp, 100);
  sprintf(tmp, "SWID : %i\r\n", r->swid);
  write(s, tmp, strlen(tmp));
  bzero(tmp, 100);
  sprintf(tmp, "Relates to : %i\r\n", r->node_to->swid);
  write(s, tmp, strlen(tmp));
  free(tmp);
  attributes_display(s, r->attributes);
  
}
