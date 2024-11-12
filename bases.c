#include "bases.h"

void bases_list(int s){
  struct dll * bs;

  bs=bases;
  if(bs!=NULL){
    bs=dll_first(bs);
    while (bs->next!=NULL){
      base_list(s, bs->payload);
      bs=bs->next;
    }
    base_list(s, bs->payload);
  }
}

void bases_display(){
  struct dll * bs;

  printf("Bases : %i\n", bases_count());
  
  bs=dll_first(bases);
  if(bs!=NULL){
    while (bs->next!=NULL){
      base_display(bs->payload);
      bs=bs->next;
    }
    base_display(bs->payload);
  }
}
  
long int bases_count(){
  long int n=0;
  struct dll * bs;
  bs=bases;
  
  n=dll_count(bs);
  return n;
}
