#include "nodes.h"

void nodes_display(struct dll * list){
  struct dll * l;

  l=list;
  if(l!=NULL){
    printf("Nodes # : %i\n", nodes_count(l));
    l=dll_first(l);
    while(l->next!=NULL){
      node_display(l->payload);
      l=l->next;
    }
    node_display(l->payload);
  }
}

long int nodes_count(struct dll * l){
  long int n;

  n=dll_count(l);

  return n;
}
  
