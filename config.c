#include "config.h"

struct config_struct * config_read(void){
  char * tmp;
  
  config=malloc(sizeof(struct config_struct));

  config->data_writer_interval=3;

  tmp=malloc(1000);
  bzero(tmp,1000);
  sprintf(tmp,"./");
  
  config->data_dir=malloc(strlen(tmp));
  config->data_dir=strncpy(config->data_dir, tmp, strlen(tmp));
  free(tmp);
  
  return config;  
}
