#include "writer.h"

void write_relation_attribute(struct base_struct *b, struct node_struct *n, struct relation_struct * r, struct attribute_struct *a){
  printf("writing relation attribute %i , %i, %i, %i\n", b->swid, n->swid, r->swid, a->swid);
  a->control->dirty=0;
}

void process_relation_attributes(struct base_struct * b, struct node_struct * n, struct relation_struct * r) {
  struct dll * attributes;
  struct attribute_struct * a;
  
  attributes=r->attributes;

  if(attributes!=NULL) {
    attributes=dll_first(attributes);
    while(attributes->next!=NULL) {
      a=attributes->payload;
      if(a->control->dirty==1) write_relation_attribute(b, n, r, a);//also save the base, node and relation this attributes belongs to
      attributes=attributes->next;
    }
    a=attributes->payload;
    if(a->control->dirty==1) write_relation_attribute(b, n, r, a);//also save the base, node and relation this attributes belongs to
  }
}

void write_relation(struct base_struct * b, struct node_struct * n, struct relation_struct * r) {
  printf("writing relation %i , %i, %i\n", b->swid, n->swid, r->swid);
  r->control->dirty=0;
}

void process_relation(struct base_struct * b, struct node_struct * n, struct relation_struct *r) {
  if (r->control->dirty==1) write_relation(b, n, r);
  process_relation_attributes(b, n, r);
}

void process_node_relations(struct base_struct * b, struct node_struct * n) {
  struct dll * relations;
  struct relation_struct * r;

  relations=n->relations;
  if (relations!=NULL){
    relations=dll_first(relations);
    while(relations->next!=NULL) {
      r=relations->payload;
      process_relation(b, n, r);
      relations=relations->next;	
    }
    r=relations->payload;
    process_relation(b, n, r);    
  }
}

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
  process_node_relations(b, n);
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
  struct base_struct * file_base;
  struct node_struct * n;
  struct attribute_struct * a;
  struct dll * list=NULL;
  
  FILE * fp;
  char * file_name;
  int written=0;
  long int position=0;
  char * tmp;
  long int tmp_id;
  
  if (b->control->file == NULL) {
    //never written before
    //so which file is for bases
    file_base=base_search_by_kv("name","files");
    list=node_search_by_kv(file_base->nodes, "type", "bases");
    // for now ther is oalways 1 and only 1 node for type bases...so we can get the very first node of this list
    n=list->payload;
    // make the list free
    free(list);
    a=node_get_attribute(n->attributes, "name");

    //adjust the control struct
    b->control->file=malloc(strlen(a->value)+1);
    bzero(b->control->file, strlen(a->value)+1);
    b->control->file=strncpy(b->control->file, a->value, strlen(a->value));

    printf("Writing new base %i\n", b->swid);
    fp=fopen(b->control->file, "r+");
    
    fseek(fp, 0, SEEK_SET);
    while(written==0) {
      fseek(fp, position, SEEK_SET);    
      fread(&tmp_id, sizeof(long int), 1, fp);
      
      if(tmp_id==0) {
	fseek(fp, position, SEEK_SET);    
	fwrite(&b->swid, sizeof(long int), 1, fp);
	written=1;  
      }
      
      position=position+sizeof(long int);
    }
    fclose(fp);
  } else {
    
    printf("Writing base %i\n", b->swid);
    fp=fopen(b->control->file, "r+");
    
    fseek(fp, b->control->position, SEEK_SET);
    fwrite(&b->swid, sizeof(long int), 1, fp);
    fclose(fp);
  }  
  
  b->control->dirty=0;
}

void process_base(struct base_struct * b) {
  if(b->control->dirty==1) write_base(b);
  process_base_attributes(b);
  process_nodes(b);
}

void process_bases(struct dll * bs){
  struct base_struct *b;

  bs=dll_first(bs);
  while(bs->next!=NULL) {
    b=bs->payload;
    if ((b->swid!=0) && (attribute_exists_by_kv(b->attributes, "name", "files")==0)) { // the config base is not written to datafiles (created at startup from the config (text) file)
                                                                                       // Also the base with files will not be written to disk
      process_base(b);
    } 
    bs=bs->next;
  }
  b=bs->payload;
  if ((b->swid!=0) && (attribute_exists_by_kv(b->attributes, "name", "files")==0)) { // the config base is not written to datafiles (created at startup from the config (text) file)
                                                                                     // Also the base with files will not be written to disk
    process_base(b);
  } 
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
