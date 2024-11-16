#include "attribute.h"

void attribute_list(int s, struct attribute_struct * a){
  char * tmp;
  
  if(a!=NULL){
    tmp=malloc(strlen(a->key)+strlen(a->value)+10+10);//+10 for the swid and +10 for the extra spaces
    bzero(tmp, strlen(a->key)+strlen(a->value)+10+10);
    sprintf(tmp, "%i  %s  %s\r\n", a->swid, a->key, a->value);
    write(s, tmp, strlen(tmp));
  }
}

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

void attribute_display(int s, struct attribute_struct * a){
  char * tmp;
  
  if(a!=NULL){
    tmp=malloc(strlen(a->key)+strlen(a->value)+10+10);//+10 for the swid and +10 for the extra spaces
    bzero(tmp, strlen(a->key)+strlen(a->value)+10+10);
    sprintf(tmp, "%i  %s  %s\r\n", a->swid, a->key, a->value);
    write(s, tmp, strlen(tmp));
  }
}
