#include "reader.h"

void file_in_administration(char * file_name, char * file_type) {
  struct node_struct * n;
  struct base_struct * b;
  struct attribute_struct * a;
  char * tmp;
  FILE * fp;
  long int file_size;
  
  // CReate the file in the administration
  n=node_new(0);
  b=base_search_by_kv("name","files");
  b->nodes=dll_add(b->nodes, n);
  a=attribute_new(0, "name", file_name);
  n->attributes=dll_add(n->attributes, a);
  a=attribute_new(0, "type", file_type);
  n->attributes=dll_add(n->attributes, a);

  fp=fopen(file_name, "r");
  fseek(fp, 0, SEEK_END);
  file_size=ftell(fp);
  fclose(fp);
  
  tmp=malloc(100);
  bzero(tmp, 100);

  sprintf(tmp, "%i", file_size);
  a=attribute_new(0, "file_size", tmp);
  n->attributes=dll_add(n->attributes, a);

  free(tmp);
  free(file_name);
}

void create_file(char * file_name) {
  FILE * fp;
  char * buffer;
  long int max_file_size;

  char * tmp;
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp,"Create file : %s", file_name);
  logger(tmp);
  free(tmp);
  
  max_file_size=config_get_int("max_file_size");
  //create the actual file
  fp=fopen(file_name, "w+");

  //initialize a buffer to write to the new file
  buffer=malloc(max_file_size);
  bzero(buffer, max_file_size);
  
  fwrite(buffer, max_file_size, 1, fp);
  fflush(fp);
  fclose(fp);
}

char * construct_file_name(char * dir_name, char * file_name) {
  char * fn, * dn, * totaal, * tmp;
  fn=config_get_char(file_name);
  dn=config_get_char(dir_name);

  totaal=malloc(strlen(fn)+strlen(dn)+1);
  bzero(totaal, strlen(fn)+strlen(dn)+1);
  strncpy(totaal, dn, strlen(dn));
  tmp=totaal+strlen(dn);
  tmp=strncpy(tmp, fn, strlen(fn));

  free(fn);
  free(dn);
  
  return totaal;
}

void relations_attributes_read() {
  struct dll * bs;
  char * file_name;
  FILE * fp;
  long int tmp_attribute_swid;
  long int tmp_base_swid;
  long int tmp_node_swid;
  long int tmp_relation_swid;
  char * tmp_k, * tmp_v;
  long int file_size;
  long int max_attribute_size;
  struct base_struct * base;
  struct node_struct * node;
  struct relation_struct * relation;
  struct attribute_struct * attribute;
  long int len;
  long int position;
  
  logger("Reading relations attributes");

  bs=bases;

  file_name=construct_file_name("data_dir", "relation_attribute_file");

  char * tmp;
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "Relation attribute file : %s", file_name);
  logger(tmp);
  free(tmp);
  
  //Let's go girls
  fp=fopen(file_name, "r+");
  if (fp!=NULL) {
    //the file exists

    max_attribute_size=config_get_int("max_attribute_size");
    //determine the file_size
    // ahum...daar is een veld in de controlstructure voor
    fseek(fp, 0, SEEK_END);
    file_size=ftell(fp);
    position=0;
    while (position+max_attribute_size<file_size) {
      fseek(fp, position, SEEK_SET);
      fread(&tmp_attribute_swid, sizeof(long int), 1, fp);
      if (tmp_attribute_swid!=0) {
	fread(&tmp_base_swid, sizeof(long int), 1, fp);
	fread(&tmp_node_swid, sizeof(long int), 1, fp);
	fread(&tmp_relation_swid, sizeof(long int), 1, fp);
	fread(&len, sizeof(long int), 1, fp);
	tmp_k=malloc(len+1);
	bzero(tmp_k, len+1);
	fread(tmp_k, len, 1, fp);
	fread(&len, sizeof(long int), 1, fp);
	tmp_v=malloc(len+1);
	bzero(tmp_v, len+1);
	fread(tmp_v, len, 1,fp);

	attribute=attribute_new(tmp_attribute_swid, tmp_k, tmp_v);
	free(tmp_k);
	free(tmp_v);
	
	base=base_search_by_swid(tmp_base_swid);
	node=node_search_by_swid(base, tmp_node_swid);
	relation=relation_search_by_swid(node, tmp_relation_swid);
	relation->attributes=dll_add(relation->attributes, attribute);
	attribute->control->file=malloc(strlen(file_name)+1);
	bzero(attribute->control->file, strlen(file_name)+1);
	attribute->control->file=strncpy(attribute->control->file, file_name, strlen(file_name));
	attribute->control->position=position;
	attribute->control->dirty=0;
	attribute->control->status=0;
      }
      position=position+max_attribute_size;
    }
    fclose(fp);
    
  } else {
    //the file does not exist ..create it
    create_file(file_name);
  }
  file_in_administration(file_name, "relations_attributes");
}

void relations_read() {
  struct dll * bs;
  char * file_name;
  FILE * fp;
  long int position;
  long int tmp_relation_swid;
  long int tmp_base_swid;
  long int tmp_node_swid;
  long int tmp_node_to_swid;
  long int file_size;
  struct node_struct * node, * node_to;
  struct base_struct * base;
  struct relation_struct * relation;
  
  logger("Reading relations");
  bs=bases;

  file_name=construct_file_name("data_dir", "relation_file");
  char * tmp;
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp,"Relation file : %s", file_name);
  logger(tmp);
  free(tmp);
  
  //Let's go girls
  fp=fopen(file_name, "r+");
  if (fp!=NULL) {
    //the file exists
    fseek(fp, 0, SEEK_END);
    file_size=ftell(fp);
    position=0;
    while (position+4*sizeof(long int)<file_size) {//4 x long int omdat er een relation_swid en een base_sid en een node_swid en een node_to_swid  staan
      fseek(fp, position, SEEK_SET);
      fread(&tmp_relation_swid, sizeof(long int), 1, fp);
      if (tmp_relation_swid!=0) {
	fread(&tmp_base_swid, sizeof(long int), 1, fp);
	fread(&tmp_node_swid, sizeof(long int), 1, fp);
	fread(&tmp_node_to_swid, sizeof(long int), 1, fp);

	base=base_search_by_swid(tmp_base_swid);
	node=node_search_by_swid(base, tmp_node_swid);
	node_to=node_search_by_swid(base, tmp_node_to_swid);

	relation=relation_new(tmp_relation_swid, node_to);
	node->relations=dll_add(node->relations, relation);

	relation->control->file=malloc(strlen(file_name)+1);
	bzero(relation->control->file, strlen(file_name)+1);
	relation->control->file=strncpy(relation->control->file, file_name, strlen(file_name));
        relation->control->position=position;
	relation->control->dirty=0;
	relation->control->status=0;
      }
      position=position+4*sizeof(long int);
    }
    fclose(fp);

  } else {
    create_file(file_name);
  }

  file_in_administration(file_name, "relations");
}

void nodes_attributes_read() {
  struct dll * bs;
  char * file_name;
  FILE * fp;
  long int tmp_attribute_swid;
  long int tmp_base_swid;
  long int tmp_node_swid;
  char * tmp_k, * tmp_v;
  long int file_size;
  long int max_attribute_size;
  struct attribute_struct * attribute;
  struct base_struct * base;
  struct node_struct * node;
  long int len;
  long int position;
  
  logger("Reading nodes attributes");

  bs=bases;

  file_name=construct_file_name("data_dir", "node_attribute_file");

  char * tmp;
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp,"Node attribute file : %s", file_name);
  free(tmp);

  //Let's go girls
  fp=fopen(file_name, "r+");
  if (fp!=NULL) {
    //the file exists

    max_attribute_size=config_get_int("max_attribute_size");
    //determine the file_size
    // ahum...daar is een veld in de controlstructure voor
    fseek(fp, 0, SEEK_END);
    file_size=ftell(fp);
    position=0;
    while (position+max_attribute_size<file_size) {
      fseek(fp, position, SEEK_SET);
      fread(&tmp_attribute_swid, sizeof(long int), 1, fp);
      if (tmp_attribute_swid!=0) {
	fread(&tmp_base_swid, sizeof(long int), 1, fp);
	fread(&tmp_node_swid, sizeof(long int), 1, fp);
	fread(&len, sizeof(long int), 1, fp);
	tmp_k=malloc(len+1);
	bzero(tmp_k, len+1);
	fread(tmp_k, len, 1, fp);
	fread(&len, sizeof(long int), 1, fp);
	tmp_v=malloc(len+1);
	bzero(tmp_v, len+1);
	fread(tmp_v, len, 1,fp);

	attribute=attribute_new(tmp_attribute_swid, tmp_k, tmp_v);
	base=base_search_by_swid(tmp_base_swid);
	node=node_search_by_swid(base, tmp_node_swid);
	node->attributes=dll_add(node->attributes, attribute);
	attribute->control->file=malloc(strlen(file_name)+1);
	bzero(attribute->control->file, strlen(file_name)+1);
	attribute->control->file=strncpy(attribute->control->file, file_name, strlen(file_name));
	attribute->control->position=position;
	attribute->control->dirty=0;
	attribute->control->status=0;

      }
      position=position+max_attribute_size;
    }
    fclose(fp);
    
  } else {
    //the file does not exist ..create it
    create_file(file_name);
  }
  file_in_administration(file_name, "nodes_attributes");
}


void nodes_read() {
  struct dll * bs;
  char * file_name;
  FILE * fp;
  long int position;
  long int tmp_swid;
  long int tmp_base_swid;
  long int file_size;
  struct node_struct * node;
  struct base_struct * base;
  
  logger("Reading nodes");
  bs=bases;

  file_name=construct_file_name("data_dir", "node_file");

  char * tmp;
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "Base attribute file : %s", file_name);
  logger(tmp);
  free(tmp);

  //Let's go girls
  fp=fopen(file_name, "r+");
  if (fp!=NULL) {
    //the file exists
    fseek(fp, 0, SEEK_END);
    file_size=ftell(fp);
    position=0;
    while (position+2*sizeof(long int)<file_size) {//2 x long int omdat er een node_swid en een base_sid staan
      fseek(fp, position, SEEK_SET);
      fread(&tmp_swid, sizeof(long int), 1, fp);
      if (tmp_swid!=0) {
	fread(&tmp_base_swid, sizeof(long int), 1, fp);

	node=node_new(tmp_swid);
	base=base_search_by_swid(tmp_base_swid);
	base->nodes=dll_add(base->nodes, node);
	node->control->file=malloc(strlen(file_name)+1);
	bzero(node->control->file, strlen(file_name)+1);
	node->control->file=strncpy(node->control->file, file_name, strlen(file_name));
        node->control->position=position;
	node->control->dirty=0;
	node->control->status=0;
      }
      position=position+2*sizeof(long int);
    }
    fclose(fp);

  } else {
    create_file(file_name);
  }

  file_in_administration(file_name, "nodes");
}

void bases_attributes_read() {
  struct dll * bs;
  char * file_name;
  FILE * fp;
  long int tmp_id;
  long int tmp_base_id;
  char * tmp_k, * tmp_v;
  long int file_size;
  long int max_attribute_size;
  struct attribute_struct * attribute;
  struct base_struct * base;
  long int len;
  long int position;
  
  logger("Reading bases attributes");

  bs=bases;

  file_name=construct_file_name("data_dir", "base_attribute_file");

  char * tmp;
  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp,"Base attribute file : %s", file_name);
  logger(tmp);
  free(tmp);
  
  //Let's go girls
  fp=fopen(file_name, "r+");
  if (fp!=NULL) {
    //the file exists

    max_attribute_size=config_get_int("max_attribute_size");
    //determine the file_size
    // ahum...daar is een veld in de controlstructure voor
    fseek(fp, 0, SEEK_END);
    file_size=ftell(fp);
    position=0;
    while (position+max_attribute_size<file_size) {
      fseek(fp, position, SEEK_SET);
      fread(&tmp_id, sizeof(long int), 1, fp);
      if (tmp_id!=0) {
	fread(&tmp_base_id, sizeof(long int), 1, fp);
	fread(&len, sizeof(long int), 1, fp);
	tmp_k=malloc(len+1);
	bzero(tmp_k, len+1);
	fread(tmp_k, len, 1, fp);
	fread(&len, sizeof(long int), 1, fp);
	tmp_v=malloc(len+1);
	bzero(tmp_v, len+1);
	fread(tmp_v, len, 1,fp);

	attribute=attribute_new(tmp_id, tmp_k, tmp_v);
	base=base_search_by_swid(tmp_base_id);
	base->attributes=dll_add(base->attributes, attribute);
	attribute->control->file=malloc(strlen(file_name)+1);
	bzero(attribute->control->file, strlen(file_name)+1);
	attribute->control->file=strncpy(attribute->control->file, file_name, strlen(file_name));
	attribute->control->position=position;
	attribute->control->dirty=0;
	attribute->control->status=0;

      }
      position=position+max_attribute_size;
    }
    fclose(fp);
    
  } else {
    //the file does not exist ..create it
    create_file(file_name);
  }
  file_in_administration(file_name, "bases_attributes");
}

void bases_read() {
  char * totaal, * tmp;
  struct dll * bs;
  struct base_struct * b;
  FILE * fp;
  unsigned long int file_size=0;
  struct node_struct * n;
  struct attribute_struct * a;
  long int position;
  char * buffer=NULL;
  long int base_id;
  
  logger("Reading Bases");

  bs=bases;

  totaal=construct_file_name("data_dir","base_file");

  tmp=malloc(100);
  bzero(tmp, 100);
  sprintf(tmp, "Base file : %s", totaal);
  logger(tmp);
  free(tmp);
       
  fp=fopen(totaal, "r+");
  if (fp!=NULL) {
    tmp=malloc(100);
    bzero(tmp, 100);

    sprintf(tmp, "Basefile exists : %s", totaal);
    logger(tmp);
    free(tmp);

    //now comes the heavy lifting : reading from the file into bases

    //first determine lenth
    fseek(fp, 0, SEEK_END);
    file_size=ftell(fp);
    for(position=0; position<=file_size-sizeof(long int); position=position+sizeof(long int)){
      fseek(fp, position, SEEK_SET);
      fread(&base_id, sizeof(long int), 1, fp);
      if (base_id!=0){
	char * tmp;
	tmp=malloc(100);
	bzero(tmp, 100);
	sprintf(tmp, "Position : %i Base id %i", position, base_id);
	logger(tmp);
	free(tmp);
  
	struct base_struct * b;

	b=base_new(base_id);
	b->control->file=malloc(strlen(totaal)+1);
	bzero(b->control->file, strlen(totaal)+1);
	b->control->file=strncpy(b->control->file, totaal, strlen(totaal));
	b->control->position=position;
	bs=dll_add(bs, b);
      }
    }
    fclose(fp);
  } else {
    char * tmp;
    tmp=malloc(100);
    bzero(tmp, 100);
    sprintf(tmp, "Create basefile : %s", totaal);
    logger(tmp);
    free(tmp);
  
    //create the actual file
    create_file(totaal);
  }
    
  // CReate the file in the administration
  file_in_administration(totaal, "bases");
}

void reader() {
  struct dll * bs;
  struct base_struct * b;
  struct attribute_struct * a;

  logger("Reading data into g10");
  bs=bases;
  b=base_new(0);
  bs=dll_add(bs, b); //new file base
  a=attribute_new(0,"name", "files");
  b->attributes=dll_add(b->attributes, a);
  
  bases_read();
  bases_attributes_read();
  nodes_read();
  nodes_attributes_read();
  relations_read();
  relations_attributes_read();
}
