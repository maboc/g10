#include "relation.h"

struct relation_struct * relation_new(struct node_struct * n){
  struct relation_struct * r;

  r=malloc(sizeof(struct relation_struct));
  r->swid=swid++;
  r->node_to=n;
  r->attributes=NULL;

  return r;
}

void relation_display(struct relation_struct * r){

  printf("--- Relation ---\n");
  printf("SWID : %i\n", r->swid);
  printf("Relates to : %i\n", r->node_to->swid);
  attributes_display(r->attributes);
  
}
