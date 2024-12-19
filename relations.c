#include "relations.h"

int relations_search_2(struct dll * relations_list, char * key, char * value) {
  int antwoord=0;
  struct relation_struct * relation;
  
  if(relations_list!=NULL) {
    relations_list=dll_first(relations_list);
    while(relations_list->next!=NULL) {
      relation=relations_list->payload;
      antwoord=antwoord+relation_search(relation->attributes, key, value);

      relations_list=relations_list->next;
    }
    relation=relations_list->payload;
    antwoord=antwoord+relation_search(relation->attributes, key, value);
  }
  return antwoord;  
}

struct dll * relations_search(struct dll * nodes_list, char * key, char * value){
  struct dll * results=NULL;
  struct node_struct * node;
  int antwoord=0;
  
  if (nodes_list!=NULL) {
    nodes_list=dll_first(nodes_list);

    while (nodes_list->next!=NULL) {
      node=nodes_list->payload;
      antwoord=relations_search_2(node->relations, key, value);
      if (antwoord>0) results=dll_add(results, node);
      
      nodes_list=nodes_list->next;
    }
    node=nodes_list->payload;
    antwoord=relations_search_2(node->relations, key, value);
    if (antwoord>0) results=dll_add(results, node);
  }
  
  return results;
}

void relations_display(int s, struct dll * list){
  struct dll * l;

  l=list;
  if(l!=NULL){
    char * tmp;
    tmp=malloc(100);
    bzero(tmp, 100);
    sprintf(tmp, "Relations # : %i\n", relations_count(l));
    write(s, tmp, strlen(tmp));
    free(tmp);
    
    l=dll_first(l);
    while(l->next!=NULL){
      relation_display(s, l->payload);
      l=l->next;
    }
    relation_display(s, l->payload);
  }
}

long int relations_count(struct dll * l){
  long int n;

  n=dll_count(l);

  return n;
}
  
