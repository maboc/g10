#include "node.h"

struct node_struct * node_new(){

  struct node_struct * n;

  n=malloc(sizeof(struct node_struct));
  bzero(n, sizeof(struct node_struct));

  n->swid=swid++;
  n->attributes=NULL;
  n->relations=NULL;

  return n;
}

void node_display(struct node_struct * node){
  struct dll * l;
  
  if(node!=NULL){
    printf("--- Node ---\n");
    printf("Swid : %i\n", node->swid);
    l=node->attributes;
    attributes_display(l);
    l=node->relations;
    relations_display(l);
  }
}

struct node_struct * node_search_by_swid(struct base_struct * base, long int node_swid){
  struct node_struct * tmp;
  struct node_struct * n=NULL;
  struct dll * nodes;
  int gevonden=0;

  nodes=dll_first(base->nodes);

  while((nodes->next!=NULL) && (gevonden==0)){
    tmp=nodes->payload;
    if (tmp->swid==node_swid){
      n=nodes->payload;
      gevonden=1;
    }
    nodes=nodes->next;
  }
  tmp=nodes->payload;
  if (tmp->swid==node_swid)
    n=nodes->payload;
  
  return n;
}
