#include "relations.h"

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
  
