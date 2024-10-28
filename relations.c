#include "relations.h"

void relations_display(struct dll * list){
  struct dll * l;

  l=list;
  if(l!=NULL){
    printf("Relations # : %i\n", relations_count(l));
    l=dll_first(l);
    while(l->next!=NULL){
      relation_display(l->payload);
      l=l->next;
    }
    relation_display(l->payload);
  }
}

long int relations_count(struct dll * l){
  long int n;

  n=dll_count(l);

  return n;
}
  
