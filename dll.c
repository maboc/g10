#include "dll.h"

struct dll * dll_new(){
  struct dll * list;

  list=malloc(sizeof(struct dll));
  
  list->prev=NULL;
  list->next=NULL;
  list->payload=NULL;
  
  return list;
}

struct dll * dll_add(struct dll * list, void * payload){
  struct dll * l;
  
  if(list==NULL){
    l=dll_new();
    l->payload=payload;
  } else{

    list=dll_last(list);
    l=dll_new();
    list->next=l;
    l->prev=list;
    l->payload=payload;
  }
  return l;
}


struct dll * dll_last(struct dll * list){
  struct dll * l;

  if(list!=NULL){
    l=list;
    while(l->next!=NULL){
      l=l->next;
    }
  }
  return l;
}

long int dll_count(struct dll * list){
  long int n=0;

  if(list==NULL){
    n=0;
  }else{
    list=dll_first(list);
    n=1;
    while (list->next!=NULL){
      n=n+1;
      list=list->next;
    }
  }

  return n;
}

struct dll * dll_first(struct dll * list){
  if(list!=NULL){
    while (list->prev!=NULL){
      list=list->prev;
    }
  }
  
  return list;
}
