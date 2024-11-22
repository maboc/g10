#include "config.h"

int config_get_int(char * key){
  struct base_struct * config_base;
  struct node_struct * config_node;
  struct attribute_struct * attribute;
  int n=0;
  
  config_base=base_search_by_swid(0); //config is always base 0
  config_node=config_base->nodes->payload; //the config base has only 1 node
  attribute=attribute_search_by_key(config_node->attributes, key);

  if (attribute!=NULL) n=atoi(attribute->value);
  
  return n;
}

struct dll * config_init(void){
  struct dll * bs;
  struct base_struct * config_base=NULL;
  struct node_struct * config_node=NULL;
  struct attribute_struct * attr;

  bs=bases;
  
  config_base=base_new();
  attr=attribute_new("name", "config");
  config_base->attributes=dll_add(config_base->attributes, attr);

  bs=dll_add(bs, config_base);
  
  config_node=node_new();
  attr=attribute_new("node", "config");
  config_node->attributes=dll_add(config_node->attributes, attr);
  attr=attribute_new("data_writer_interval", "3");
  config_node->attributes=dll_add(config_node->attributes, attr);
  attr=attribute_new("data_dir", "./");
  config_node->attributes=dll_add(config_node->attributes, attr);

  config_base->nodes=dll_add(config_base->nodes, config_node);

  return bs;
}
