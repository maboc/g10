#include "handler.h"

void * handler(void * sck){
  int s = *(int *) sck;

  output_line(s, "Welcome G10\r\n");
  
  return NULL;
}
