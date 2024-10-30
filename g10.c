#include "g10.h"

int main(int argc, char ** argv){
  
  printf("g10\n");

  data_load();
  
  //base_display(base);

  bases_display();

  listener_start(NULL);
  
  return 0;
}
