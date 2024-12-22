#include "attribute.h"

struct attribute_struct * attribute_search_by_swid(struct dll * attribute_list, long int swid_gezocht) {
  struct attribute_struct * a=NULL, * result=NULL;
  int gevonden=0;

  if (attribute_list!=NULL) {
    attribute_list=dll_first(attribute_list);
    while (attribute_list->next!=NULL && gevonden==0) {
      a=attribute_list->payload;
      if (a->swid==swid_gezocht) {
	result=a;
	gevonden=1;
      }
      attribute_list=attribute_list->next;
    }
    a=attribute_list->payload;
    if (a->swid==swid_gezocht) result=a;
  }
  return result;
}

int attribute_exists_by_kv(struct dll * list, char * key, char * value) {
  int r=0;
  struct attribute_struct * a;

  if (list!=NULL){
    list=dll_first(list);

    while((list->next!=NULL) && (r==0)) {
      a=list->payload;
      if ((strncmp(a->key, key, strlen(a->key))==0) && (strncmp(a->value, value, strlen(a->value))==0))	r=1;
      list=list->next;
    }
    a=list->payload;
    if ((strncmp(a->key, key, strlen(a->key))==0) && (strncmp(a->value, value, strlen(a->value))==0)) r=1;
  }
  return r;
}

struct attribute_struct * attribute_search_by_key(struct dll * list, char * key){
  struct attribute_struct * a=NULL, * a_tmp=NULL;
  int n;
  
  if (list!=NULL){
    list=dll_first(list);
    while (list->next!=NULL){
      a_tmp=list->payload;
      if (strncmp(key, a_tmp->key, strlen(key))==0) a=a_tmp;
      list=list->next;
    }
    a_tmp=list->payload;
    if (strncmp(key, a_tmp->key, strlen(key))==0) a=a_tmp;
  }

  return a;
}

void attribute_list(int s, struct attribute_struct * a){
  char * tmp;
  
  if(a!=NULL){
    tmp=malloc(strlen(a->key)+strlen(a->value)+10+10);//+10 for the swid and +10 for the extra spaces
    bzero(tmp, strlen(a->key)+strlen(a->value)+10+10);
    sprintf(tmp, "%i  %s  %s\r\n", a->swid, a->key, a->value);
    write(s, tmp, strlen(tmp));
  }
}

struct attribute_struct * attribute_new(long int bestaande_swid, char * key, char * value){
  struct attribute_struct * a;
  struct control_struct * c;

  a=malloc(sizeof(struct attribute_struct));
  bzero(a, sizeof(struct attribute_struct));

  c=malloc(sizeof(struct control_struct));
  if (bestaande_swid!=0) {
    a->swid=bestaande_swid;
    if (bestaande_swid> swid) swid=bestaande_swid;
    c->dirty=0;
  } else {
    c->dirty=1;
    a->swid=swid++;
  }

  a->control=c;
  
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
