#include "nodes.h"

struct dll * nodes_search(struct dll * nodes, char * key, char * value){
  struct dll * result=NULL;
  struct node_struct *n;
  
  if (nodes!=NULL){
    nodes=dll_first(nodes);

    while(nodes->next!=NULL){
      n=nodes->payload;
   
      if (node_match_attribute(n, key, value)>0) result=dll_add(result, n);
   
      nodes=nodes->next;
    }
    n=nodes->payload;
    if (node_match_attribute(n, key, value)>0) result=dll_add(result, n);
  }
  return result;
}
    

void nodes_display(int s, struct dll * list){
  struct dll * l;

  l=list;
  if(l!=NULL){
    char * tmp;
    tmp=malloc(100);
    bzero(tmp, 100);
    sprintf(tmp,"Nodes # : %i\r\n", nodes_count(l));
    write(s, tmp, strlen(tmp));
    free(tmp);
    
    l=dll_first(l);
    while(l->next!=NULL){
      node_display(s, l->payload);
      l=l->next;
    }
    node_display(s, l->payload);
  }
}

long int nodes_count(struct dll * l){
  long int n;

  n=dll_count(l);

  return n;
}
  
