#include "node.h"


struct dll * node_delete_inverse_relation(struct dll * inverse_relations, struct node_struct * node){
  struct dll * r=NULL;
  struct dll * prev_ir, * current_ir, * next_ir;

  if (inverse_relations != NULL) {
    if ((inverse_relations->prev==NULL) && (inverse_relations->next==NULL)) {
      //there is only one entry....then this must be the one
      free(inverse_relations);
      r=NULL;
    } else {
      //apperantly there are more then 1 relations pointing towards this node
      inverse_relations=dll_first(inverse_relations);
      int gevonden=0;
      while ((inverse_relations->next!=NULL) && (gevonden!=1)) {
	if (inverse_relations->payload==node) {
	  //yes...gevonden
	  gevonden=1;
	  
	  prev_ir=inverse_relations->prev;
	  current_ir=inverse_relations;
	  next_ir=inverse_relations->next;

	  free(current_ir);
	  if (prev_ir==NULL){
	    next_ir->prev=NULL;
	    inverse_relations=next_ir;
	  } else if (next_ir==NULL) {
	    prev_ir->next=NULL;
	    inverse_relations=prev_ir;
	  } else {
	    prev_ir->next=next_ir;
	    next_ir->prev=prev_ir;
	    inverse_relations=prev_ir;
	  }
	}
	inverse_relations=inverse_relations->next;
      }
      if (inverse_relations->payload==node) {
	struct dll * tmp;
	tmp=inverse_relations;
	inverse_relations->prev->next==NULL;
	free(tmp);
      }      
      r=inverse_relations;
    }
  }
  return r;
}

struct dll * node_search_by_kv(struct dll * list, char * k, char *v){
  struct dll * result=NULL;
  struct node_struct * n;
  
  if (list!=NULL) {
    list=dll_first(list);

    while (list->next!=NULL) {
      n=list->payload;
      if (attribute_exists_by_kv(n->attributes, k, v)==1) result=dll_add(result, n);
      list=list->next;
    }
    n=list->payload;
    if (attribute_exists_by_kv(n->attributes, k, v)==1) result=dll_add(result, n);
  }
  return result;
}

struct attribute_struct * node_get_attribute(struct dll * list, char * key) {
  struct attribute_struct * a=NULL, * tmp;
  int gevonden=0;
  
  list=dll_first(list);
  while(list->next!=NULL && gevonden==0) {
    tmp=list->payload;
    if (strncmp(tmp->key, key, strlen(key))==0) {
      gevonden=1;
      a=tmp;
    }
    tmp=list->payload;
    if (strncmp(tmp->key, key, strlen(key))==0) {
      a=tmp;
    }
  }
  return a;
}

int node_match_attribute(struct node_struct * node, char * key, char * value){
  struct dll * list;
  struct attribute_struct * attr;
  int result=0;

  if(node->attributes!=NULL){
    list=node->attributes;
    list=dll_first(list);
    while (list->next!=NULL){
      attr=list->payload;
      if ((strncmp(attr->key, key, strlen(key))==0) && (strncmp(attr->value, value, strlen(value))==0)) result++;
      list=list->next;
    }
    attr=list->payload;
    if ((strncmp(attr->key, key, strlen(key))==0) && (strncmp(attr->value, value, strlen(value))==0)) result++;
  }
  return result;
}

struct node_struct * node_new(long int bestaande_swid){

  struct node_struct * n;
  struct control_struct * c;

  n=malloc(sizeof(struct node_struct));
  bzero(n, sizeof(struct node_struct));

  c=malloc(sizeof(struct control_struct));
  c->file=NULL;
  c->position=-1;
  c->status=0;
  n->control=c;

  if (bestaande_swid==0) {
    n->swid=swid++;
    c->dirty=1;
  } else {
    n->swid=bestaande_swid;
    c->dirty=1;
    if (bestaande_swid>swid) swid=bestaande_swid;
  }
  n->attributes=NULL;
  n->relations=NULL;
  n->inverse_relations=NULL;
  
  return n;
}

void node_display(int s, struct node_struct * node){
  struct dll * l;
  
  if(node!=NULL){
    char * tmp;

    tmp=malloc(100);
    bzero(tmp, 100);
    sprintf(tmp,"--- Node ---\r\n");
    write(s, tmp, strlen(tmp));
    bzero(tmp,100);
    sprintf(tmp, "Swid : %i\r\n", node->swid);
    write(s, tmp, strlen(tmp));
    bzero(tmp, 100);
    sprintf(tmp,"Inverse relations : %i\r\n", dll_count(node->inverse_relations));
    write(s, tmp, strlen(tmp));
    free(tmp);
    l=node->attributes;
    attributes_display(s, l);
    l=node->relations;
    relations_display(s, l);
  }
}

struct node_struct * node_search_by_swid(struct base_struct * base, long int node_swid){
  struct node_struct * tmp;
  struct node_struct * n=NULL;
  struct dll * nodes;
  int gevonden=0;

  nodes=dll_first(base->nodes);

  while((nodes->next!=NULL) && (gevonden==0)){
    tmp=nodes->payload;
    if (tmp->swid==node_swid){
      n=nodes->payload;
      gevonden=1;
    }
    nodes=nodes->next;
  }
  tmp=nodes->payload;
  if (tmp->swid==node_swid)
    n=nodes->payload;
  
  return n;
}
