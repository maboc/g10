#include "attributes.h"

void attributes_list(int s, struct dll * l){
  char * tmp;
  
  if(l!=NULL){
    tmp=malloc(100);
    bzero(tmp, 100);
    
    sprintf(tmp, "Attributes # : %i\n", attributes_count(l));
    write(s, tmp, strlen(tmp));
    free(tmp);
    l=dll_first(l);
    while(l->next!=NULL){
      attribute_list(s, l->payload);
      l=l->next;
    }
    attribute_list(s, l->payload);
  }
}

void attributes_display(struct dll * l){
  if(l!=NULL){
    printf("Attributes # : %i\n", attributes_count(l));
    l=dll_first(l);
    while(l->next!=NULL){
      attribute_display(l->payload);
      l=l->next;
    }
    attribute_display(l->payload);
  }
}

long int attributes_count(struct dll * list){
  long int n;

  n=dll_count(list);

  return n;
}
