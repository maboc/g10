#include "g10.h"

int main(int argc, char ** argv){
  
  printf("g10\r\n");

  bases=config_init();
  if (bases!=NULL){  
    //   data_load();
    reader();

    writer_start(NULL);
  
    //base_display(base);

    //  bases_display(s, bases);

    listener_start(NULL);

  }
  return 0;
}
