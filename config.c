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
  struct dll * bs=NULL;
  struct base_struct * config_base=NULL;
  struct node_struct * config_node=NULL;
  struct attribute_struct * attr;
  FILE * cfg_file;
  char * cfg_file_name;
  char * config_line;

  printf("Configure the system\n");
  
  cfg_file_name=malloc(strlen("g10.cfg")+1); // Yes....the name of the config file is hardcoded
  bzero(cfg_file_name, strlen("g10.cfg")+1);
  cfg_file_name=strncpy(cfg_file_name, "g10.cfg", strlen("g10.cfg"));
  printf("Config file : %s\n", cfg_file_name);
  cfg_file=fopen(cfg_file_name, "r"); // For now the configuration is readonly
  if (cfg_file!=NULL){  

    config_base=base_new();
    attr=attribute_new("name", "config");
    config_base->attributes=dll_add(config_base->attributes, attr);

    bs=dll_add(bs, config_base);
  
    config_node=node_new();
    config_base->nodes=dll_add(config_base->nodes, config_node);

    config_line=malloc(200); // configuration items can't be longer then 200 chars (for now)
    bzero(config_line, 200);
    while (fgets(config_line, 200, cfg_file)) {

      printf("%s\n", config_line);
      
    }


    
    attr=attribute_new("node", "config");
    config_node->attributes=dll_add(config_node->attributes, attr);
    attr=attribute_new("data_writer_interval", "3");
    config_node->attributes=dll_add(config_node->attributes, attr);
    attr=attribute_new("data_dir", "./");
    config_node->attributes=dll_add(config_node->attributes, attr);

    
  } else {
    printf("No config file found (%s)\n", cfg_file_name);
  }
  
  return bs;
}
