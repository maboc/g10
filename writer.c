#include "writer.h"

void * writer(void * data_in){
  
  while (goon==0){
    printf("Starting a writer-sweep\n");

    sleep(config_get_int("data_writer_interval"));
  }

  printf("Stopping writer\n");
  
  pthread_exit(NULL);
}

void * writer_start(void * data_in){

  printf("Starting writer\n");

  pthread_t pt;
  int rc;
  rc=pthread_create(&pt, NULL, writer, NULL);
}
