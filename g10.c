#include "g10.h"

int main(int argc, char ** argv){

  pid_t child_pid;
  
  printf("g10\r\n");

  bases=config_init();
  if (bases!=NULL){  

    child_pid=fork();
    if (child_pid==0){
      logger("G10 forked this is the child speaking");
    
    //   data_load();
    reader();

    writer_start(NULL);
  
    //base_display(base);

    //  bases_display(s, bases);

    listener_start(NULL);

    } else {
      printf("G10 forked. Child process :  %i\n", child_pid);
    }

  }
  return 0;
}
