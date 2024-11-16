#include "config.h"

struct dll * config_init(void){
  struct dll * config=NULL;
  struct node_struct * config_node;
  struct attribute_struct * attr;

  config_node=node_new();
  attr=attribute_new("data_writer_interval", "3");
  config_node->attributes=dll_add(config_node->attributes, attr);
  attr=attribute_new("data_dir", "./");
  
  config=dll_add(config, config_node);
 
  return config;  
}
