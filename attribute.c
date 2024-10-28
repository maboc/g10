#include "attribute.h"

struct attribute_struct * attribute_new(char * key, char * value){
  struct attribute_struct * a;

  a=malloc(sizeof(struct attribute_struct));
  bzero(a, sizeof(struct attribute_struct));

  a->swid=swid++;
  
  a->key=malloc(strlen(key)+1);
  bzero(a->key, strlen(key)+1);
  a->key=strncpy(a->key, key, strlen(key));

  a->value=malloc(strlen(value)+1);
  bzero(a->value, strlen(value)+1);
  a->value=strncpy(a->value, value, strlen(value));
  
  return a;
}

void attribute_display(struct attribute_struct * attribute){
  if(attribute!=NULL){
    printf("%i  %s   %s\n", attribute->swid, attribute->key, attribute->value);
  }
}
