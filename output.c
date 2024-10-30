#include "output.h"

void output_line(int socket, char * message){
  write(socket, message, strlen(message));
}
