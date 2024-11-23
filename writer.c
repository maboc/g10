#include "writer.h"

void write_node_attribute(struct base_struct * b, struct node_struct * n, struct attribute_struct * a) {
  printf("Writing node attribute %i , %i , %i\n", b->swid, n->swid, a->swid);
  a->control->dirty=0;
}

void process_node_attributes(struct base_struct * b, struct node_struct * n) {
  struct dll * attributes;
  struct attribute_struct * a;
  
  attributes=n->attributes;

  if(attributes!=NULL) {
    attributes=dll_first(attributes);
    while(attributes->next!=NULL) {
      a=attributes->payload;
      if(a->control->dirty==1) write_node_attribute(b, n, a);//also save the base this attributes belongs to
      attributes=attributes->next;
    }
    a=attributes->payload;
    if(a->control->dirty==1) write_node_attribute(b, n, a);//also save the base this attributes belongs to
  }
}

void write_node(struct base_struct * b, struct node_struct * n) {
  printf("writing node %i , %i\n", b->swid, n->swid);
  n->control->dirty=0;
  
}

void process_node(struct base_struct * b, struct node_struct * n) {
  if (n->control->dirty==1) write_node(b, n);
  process_node_attributes(b, n);  
}

void process_nodes(struct base_struct * b) {
  struct dll * nodes;
  struct node_struct * node;

  nodes=b->nodes;
  if (nodes!=NULL){
    nodes=dll_first(nodes);
    while(nodes->next!=NULL) {
      node=nodes->payload;
      process_node(b, node);
      nodes=nodes->next;	
    }
    node=nodes->payload;
    process_node(b, node);    
  }
}

void write_base_attribute(struct base_struct * b, struct attribute_struct * a) {
  printf("Writing base attribute %i , %i\n", b->swid, a->swid);
  a->control->dirty=0;
}

void process_base_attributes(struct base_struct * b){
  struct dll * attributes;
  struct attribute_struct * a;
  
  attributes=b->attributes;

  if(attributes!=NULL) {
    attributes=dll_first(attributes);
    while(attributes->next!=NULL) {
      a=attributes->payload;
      if(a->control->dirty==1) write_base_attribute(b, a);//also save the base this attributes belongs to
      attributes=attributes->next;
    }
    a=attributes->payload;
    if(a->control->dirty==1) write_base_attribute(b, a);//also save the base this attributes belongs to
  }
}

void write_base(struct base_struct * b){
  printf("Writing base %i\n", b->swid);
  b->control->dirty=0;
}

void process_base(struct base_struct *b){
  if(b->control->dirty==1) write_base(b);
  process_base_attributes(b);
  process_nodes(b);
}

void process_bases(struct dll * bs){
  struct base_struct *b;

  bs=dll_first(bs);
  while(bs->next!=NULL) {
    b=bs->payload;
    process_base(b);
    bs=bs->next;
  }
  b=bs->payload;
  process_base(b);
}

void * writer(void * data_in){
  struct dll * bs;

  bs=bases;
  
  while (goon==0) {
    printf("Starting a writer-sweep\n");

    if (bs!=NULL) {
      process_bases(bs);
    }  else {
      printf("How can there be no bases at all\n"); 
    }

    sleep(config_get_int("data_writer_interval"));
  }

  printf("Stopping writer\n");
  pthread_exit(NULL);
}

void * writer_start(void * data_in){

  printf("Starting writer\n");

  pthread_t pt;
  int rc;
  rc=pthread_create(&pt, NULL, writer, NULL);
}
