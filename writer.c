#include "writer.h"

void write_relation_attribute(struct base_struct *b, struct node_struct *n, struct relation_struct * r, struct attribute_struct *a){  
  struct base_struct * file_base;
  struct node_struct * file_node;
  struct attribute_struct * file_attribute;
  struct dll * list=NULL;
  
  FILE * fp;
  char * file_name;
  int written=0;
  long int position=0;
  char * tmp;
  long int tmp_id, len;
  long int max_attribute_size;

  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "Writing relation attribute : attribute :%i, base:%i, node:%i, relation:%i", a->swid, b->swid, n->swid, r->swid);
  logger(tmp);
  free(tmp);

  if(a->control->file==NULL) {
    //never written before 
    //so which file is for base_attributes
    file_base=base_search_by_kv("name","files");
    list=node_search_by_kv(file_base->nodes, "type", "relations_attributes");
    // for now there is always 1 and only 1 node for type relations attributes...so we can get the very first node of this list
    file_node=list->payload;
    // make the list free
    free(list);
    file_attribute=node_get_attribute(file_node->attributes, "name");

    //adjust the control struct of the attribute
    a->control->file=malloc(strlen(file_attribute->value)+1);
    bzero(a->control->file, strlen(file_attribute->value)+1);
    a->control->file=strncpy(a->control->file, file_attribute->value, strlen(file_attribute->value));

    max_attribute_size=config_get_int("max_attribute_size");
    
    fp=fopen(a->control->file, "r+");
    position=0;

    while(written==0) {
      fseek(fp, position, SEEK_SET);
      fread(&tmp_id, sizeof(long int), 1, fp);//alleen een tmp_id ophalen om te checken of deze position leeg is!!!
      if(tmp_id==0) {
	fseek(fp, position, SEEK_SET);    //de positie zetten (ook na de eerste keer..de fread verzet de pointer)
	fwrite(&a->swid, sizeof(long int), 1, fp);
	fwrite(&b->swid, sizeof(long int), 1, fp);
	fwrite(&n->swid, sizeof(long int), 1, fp);
	fwrite(&r->swid, sizeof(long int), 1, fp);
	len=strlen(a->key);
	fwrite(&len, sizeof(long int), 1, fp);
	fwrite(a->key, strlen(a->key), 1, fp);
	len=strlen(a->value);
	fwrite(&len, sizeof(long int), 1, fp);
	fwrite(a->value, strlen(a->value), 1, fp);

	written=1;
	a->control->position=position;
      }
      
      position=position+max_attribute_size;
    }
    fclose(fp);
  } else {
    fp=fopen(a->control->file, "r+");
    
    fseek(fp, a->control->position, SEEK_SET);
    fwrite(&a->swid, sizeof(long int), 1, fp);
    fwrite(&b->swid, sizeof(long int), 1, fp);
    fwrite(&n->swid, sizeof(long int), 1, fp);
    fwrite(&r->swid, sizeof(long int), 1, fp);
    len=strlen(a->key);
    fwrite(&len, sizeof(long int), 1, fp);
    fwrite(a->key, strlen(a->key), 1, fp);
    len=strlen(a->value);
    fwrite(&len, sizeof(long int), 1, fp);
    fwrite(a->value, strlen(a->value), 1, fp);
        
    fclose(fp);
  }  
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

void write_relation(struct base_struct * b, struct node_struct * n, struct relation_struct * r, struct node_struct * n_t) {
  /*******/
  struct base_struct * file_base;
  struct dll * list;
  struct node_struct * file_node;
  struct relation_struct * relation;
  struct attribute_struct * file_attribute;
  FILE * fp;
  long int position;
  int written=0;
  long int tmp_relation_swid;
  
  char * tmp;
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "writing relation: relation :%i, node :%i, relation :%i, node_to :%i", b->swid, n->swid, r->swid, n_t->swid);
  logger(tmp);
  free(tmp);
  
  if (r->control->file==NULL) {
    //never written before
    //so which file is for base_attributes
    file_base=base_search_by_kv("name","files");
    list=node_search_by_kv(file_base->nodes, "type", "relations");
    // for now there is always 1 and only 1 node for type relations...so we can get the very first node of this list
    file_node=list->payload;
    // make the list free
    free(list); // dit kan alleen omdat er maar 1 entry in zit 
    file_attribute=node_get_attribute(file_node->attributes, "name");

    //adjust the control struct of the attribute
    r->control->file=malloc(strlen(file_attribute->value)+1);
    bzero(r->control->file, strlen(file_attribute->value)+1);
    r->control->file=strncpy(r->control->file, file_attribute->value, strlen(file_attribute->value));

    fp=fopen(r->control->file, "r+");
    position=0;
    
    while(written==0) {
      fseek(fp, position, SEEK_SET);
      fread(&tmp_relation_swid, sizeof(long int), 1, fp);//alleen een tmp_id ophalen om te checken of deze position leeg is!!!
      if(tmp_relation_swid==0) {
	fseek(fp, position, SEEK_SET);    //de positie zetten (ook na de eerste keer..de fread verzet de pointer)
	fwrite(&r->swid, sizeof(long int), 1, fp);
	fwrite(&b->swid, sizeof(long int), 1, fp);
	fwrite(&n->swid, sizeof(long int), 1, fp);
	fwrite(&n_t->swid, sizeof(long int), 1, fp);

	written=1;
	r->control->position=position;
      }
      
      position=position+4*sizeof(long int);  //4 * long int : relation_swid, base_swid, node_swid, node_to_swid
    }
    fclose(fp);
  } else {
    fp=fopen(r->control->file, "r+");
    
    fseek(fp, r->control->position, SEEK_SET);
    fwrite(&r->swid, sizeof(long int), 1, fp);
    fwrite(&b->swid, sizeof(long int), 1, fp);
    fwrite(&n->swid, sizeof(long int), 1, fp);
    fwrite(&n_t->swid, sizeof(long int), 1, fp);
        
    fclose(fp);
  }
  r->control->dirty=0;
}


void process_relation(struct base_struct * b, struct node_struct * n, struct relation_struct *r) {
  if (r->control->dirty==1) write_relation(b, n, r, r->node_to);
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
  struct base_struct * file_base;
  struct node_struct * file_node;
  struct attribute_struct * file_attribute;
  struct dll * list=NULL;
  
  FILE * fp;
  char * file_name;
  int written=0;
  long int position=0;
  long int tmp_id, len;
  long int max_attribute_size;

  char * tmp;
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "Writing node attribute : attribute :%i, base :%i, node %i", a->swid, b->swid, n->swid);  
  logger(tmp);
  free(tmp);
  
  if(a->control->file==NULL) {
    //never written before
    //so which file is for base_attributes
    file_base=base_search_by_kv("name","files");
    list=node_search_by_kv(file_base->nodes, "type", "nodes_attributes");
    // for now there is always 1 and only 1 node for type base attributes...so we can get the very first node of this list
    file_node=list->payload;
    // make the list free
    free(list);
    file_attribute=node_get_attribute(file_node->attributes, "name");

    //adjust the control struct of the attribute
    a->control->file=malloc(strlen(file_attribute->value)+1);
    bzero(a->control->file, strlen(file_attribute->value)+1);
    a->control->file=strncpy(a->control->file, file_attribute->value, strlen(file_attribute->value));

    max_attribute_size=config_get_int("max_attribute_size");
    
    fp=fopen(a->control->file, "r+");
    position=0;

    while(written==0) {
      fseek(fp, position, SEEK_SET);
      fread(&tmp_id, sizeof(long int), 1, fp);//alleen een tmp_id ophalen om te checken of deze position leeg is!!!
      if(tmp_id==0) {
	fseek(fp, position, SEEK_SET);    //de positie zetten (ook na de eerste keer..de fread verzet de pointer)
	fwrite(&a->swid, sizeof(long int), 1, fp);
	fwrite(&b->swid, sizeof(long int), 1, fp);
	fwrite(&n->swid, sizeof(long int), 1, fp);
	len=strlen(a->key);
	fwrite(&len, sizeof(long int), 1, fp);
	fwrite(a->key, strlen(a->key), 1, fp);
	len=strlen(a->value);
	fwrite(&len, sizeof(long int), 1, fp);
	fwrite(a->value, strlen(a->value), 1, fp);

	written=1;
	a->control->position=position;
      }
      
      position=position+max_attribute_size;
    }
    fclose(fp);
  } else {
    fp=fopen(a->control->file, "r+");
    
    fseek(fp, a->control->position, SEEK_SET);
    fwrite(&a->swid, sizeof(long int), 1, fp);
    fwrite(&b->swid, sizeof(long int), 1, fp);
    fwrite(&n->swid, sizeof(long int), 1, fp);
    len=strlen(a->key);
    fwrite(&len, sizeof(long int), 1, fp);
    fwrite(a->key, strlen(a->key), 1, fp);
    len=strlen(a->value);
    fwrite(&len, sizeof(long int), 1, fp);
    fwrite(a->value, strlen(a->value), 1, fp);
        
    fclose(fp);
  }  
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

void write_node(struct base_struct * base, struct node_struct * node) {
  struct base_struct * file_base;
  struct dll * list;
  struct node_struct * n;
  struct attribute_struct * a;
  long int tmp_swid;
  long int tmp_base_swid;
  FILE * fp;
  long int position;
  int written=0;

  char * tmp;
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "writing node: node :%i, base :%i", node->swid, base->swid);
  logger(tmp);
  free(tmp);

  if(node->control->file==NULL) {
    //never written before
    //so which file is for base_attributes
    file_base=base_search_by_kv("name","files");
    list=node_search_by_kv(file_base->nodes, "type", "nodes");
    // for now there is always 1 and only 1 node for type nodes...so we can get the very first node of this list
    n=list->payload;
    // make the list free
    free(list); // dit kan alleen omdat er maar 1 entry in zit 
    a=node_get_attribute(n->attributes, "name");

    //adjust the control struct of the attribute
    node->control->file=malloc(strlen(a->value)+1);
    bzero(node->control->file, strlen(a->value)+1);
    node->control->file=strncpy(node->control->file, a->value, strlen(a->value));

    fp=fopen(node->control->file, "r+");
    position=0;
    
    while(written==0) {
      fseek(fp, position, SEEK_SET);
      fread(&tmp_swid, sizeof(long int), 1, fp);//alleen een tmp_id ophalen om te checken of deze position leeg is!!!
      if(tmp_swid==0) {
	fseek(fp, position, SEEK_SET);    //de positie zetten (ook na de eerste keer..de fread verzet de pointer)
	fwrite(&node->swid, sizeof(long int), 1, fp);
	fwrite(&base->swid, sizeof(long int), 1, fp);

	written=1;
	node->control->position=position;
      }
      
      position=position+2*sizeof(long int);
    }
    fclose(fp);
  } else {
    
    fp=fopen(node->control->file, "r+");
    
    fseek(fp, node->control->position, SEEK_SET);
    fwrite(&node->swid, sizeof(long int), 1, fp);
    fwrite(&base->swid, sizeof(long int), 1, fp);
        
    fclose(fp);
  }
  node->control->dirty=0;
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

void write_base_attribute(struct base_struct * base, struct attribute_struct * attribute) {
  struct base_struct * file_base;
  struct node_struct * n;
  struct attribute_struct * a;
  struct dll * list=NULL;
  
  FILE * fp;
  char * file_name;
  int written=0;
  long int position=0;
  char * tmp;
  long int tmp_id, len;
  long int max_attribute_size;

  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "Writing base attribute: attribute :%i , base :%i", base->swid, attribute->swid);
  logger(tmp);
  free(tmp);

  if(attribute->control->file==NULL) {
    //never written before
    //so which file is for base_attributes
    file_base=base_search_by_kv("name","files");
    list=node_search_by_kv(file_base->nodes, "type", "bases_attributes");
    // for now there is always 1 and only 1 node for type base attributes...so we can get the very first node of this list
    n=list->payload;
    // make the list free
    free(list);
    a=node_get_attribute(n->attributes, "name");

    //adjust the control struct of the attribute
    attribute->control->file=malloc(strlen(a->value)+1);
    bzero(attribute->control->file, strlen(a->value)+1);
    attribute->control->file=strncpy(attribute->control->file, a->value, strlen(a->value));

    max_attribute_size=config_get_int("max_attribute_size");
    
    fp=fopen(attribute->control->file, "r+");
    position=0;

    while(written==0) {
      fseek(fp, position, SEEK_SET);
      fread(&tmp_id, sizeof(long int), 1, fp);//alleen een tmp_id ophalen om te checken of deze position leeg is!!!
      if(tmp_id==0) {
	fseek(fp, position, SEEK_SET);    //de positie zetten (ook na de eerste keer..de fread verzet de pointer)
	fwrite(&attribute->swid, sizeof(long int), 1, fp);
	fwrite(&base->swid, sizeof(long int), 1, fp);
	len=strlen(attribute->key);
	fwrite(&len, sizeof(long int), 1, fp);
	fwrite(attribute->key, strlen(attribute->key), 1, fp);
	len=strlen(attribute->value);
	fwrite(&len, sizeof(long int), 1, fp);
	fwrite(attribute->value, strlen(attribute->value), 1, fp);

	written=1;
	attribute->control->position=position;
      }
      
      position=position+max_attribute_size;
    }
    fclose(fp);
  } else {
    fp=fopen(attribute->control->file, "r+");
    
    fseek(fp, attribute->control->position, SEEK_SET);
    fwrite(&attribute->swid, sizeof(long int), 1, fp);
    fwrite(&base->swid, sizeof(long int), 1, fp);
    len=strlen(attribute->key);
    fwrite(&len, sizeof(long int), 1, fp);
    fwrite(attribute->key, strlen(attribute->key), 1, fp);
    len=strlen(attribute->value);
    fwrite(&len, sizeof(long int), 1, fp);
    fwrite(attribute->value, strlen(attribute->value), 1, fp);
        
    fclose(fp);
  }  
  attribute->control->dirty=0;
}

void process_base_attributes(struct base_struct * b) {
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

  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "Writing base %i", b->swid);
  logger(tmp);
  free(tmp);
  
  if (b->control->file == NULL) {
    //never written before
    //so which file is for bases
    file_base=base_search_by_kv("name","files");
    list=node_search_by_kv(file_base->nodes, "type", "bases");
    // for now there is always 1 and only 1 node for type bases...so we can get the very first node of this list
    n=list->payload;
    // make the list free
    free(list);
    a=node_get_attribute(n->attributes, "name");

    //adjust the control struct
    b->control->file=malloc(strlen(a->value)+1);
    bzero(b->control->file, strlen(a->value)+1);
    b->control->file=strncpy(b->control->file, a->value, strlen(a->value));

    fp=fopen(b->control->file, "r+");
    
    while(written==0) {
      fseek(fp, position, SEEK_SET);    
      fread(&tmp_id, sizeof(long int), 1, fp);
      
      if(tmp_id==0) {
	fseek(fp, position, SEEK_SET);    
	fwrite(&b->swid, sizeof(long int), 1, fp);
	b->control->position=position;
	written=1;  
      }
      
      position=position+sizeof(long int);
    }
    fclose(fp);
  } else {
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
  char * tmp;

  bs=bases;
  
  while (goon==0) {
    tmp=malloc(100);
    bzero(tmp, 100);
    sprintf(tmp, "Starting a writer-sweep");
    logger(tmp);
    free(tmp);
    
    if (bs!=NULL) {
      process_bases(bs);
    }  else {
      tmp=malloc(100);
      bzero(tmp, 100);
      sprintf(tmp, "How can there be no bases at all");
      logger(tmp);
      free(tmp);
    }

    sleep(config_get_int("data_writer_interval"));
  }
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp,"Stopping writer");
  logger(tmp);
  free(tmp);
  
  pthread_exit(NULL);
}

void * writer_start(void * data_in){
  char * tmp;

  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "Starting writer");
  logger(tmp);
  free(tmp);
    
  pthread_t pt;
  int rc;
  rc=pthread_create(&pt, NULL, writer, NULL);
}
