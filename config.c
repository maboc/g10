#include "config.h"

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
  attr=attribute_new("data_writer_interval", "3");
  config_node->attributes=dll_add(config_node->attributes, attr);
  attr=attribute_new("data_dir", "./");
  config_node->attributes=dll_add(config_node->attributes, attr);

  config_base->nodes=dll_add(config_base->nodes, config_node);

  return bs;
}
