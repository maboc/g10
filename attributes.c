#include "attributes.h"

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
