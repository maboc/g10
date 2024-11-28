#include "reader.h"

void bases_read() {
  char * file_name;
  char * dir_name;
  char * totaal;
  char * tmp;
  struct dll * bs;
  struct base_struct * b;
  FILE * fp;

  struct node_struct * n;
  struct attribute_struct * a;
  
  printf("Reading Bases\n");

  bs=bases;
  
  file_name=config_get_char("base_file");
  dir_name=config_get_char("data_dir");

  totaal=malloc(strlen(file_name)+strlen(dir_name)+1);
  bzero(totaal, strlen(file_name)+strlen(dir_name)+1);
  strncpy(totaal, dir_name, strlen(dir_name));
  tmp=totaal+strlen(dir_name);
  tmp=strncpy(tmp, file_name, strlen(file_name));

  printf("Base file : %s\n", totaal);

  fp=fopen(totaal, "r+");
  if (fp!=NULL) {
    printf("Basefile exists : %s\n", totaal);
  } else {
    printf("Create basefile : %s\n", totaal);
    
    n=node_new();
    b=base_search_by_kv("name","files");
    b->nodes=dll_add(b->nodes, n);
    a=attribute_new("name", totaal);
    n->attributes=dll_add(n->attributes, a);
    a=attribute_new("type", "bases");
    n->attributes=dll_add(n->attributes, a);
  }
  
  free(totaal);
}

void reader() {
  struct dll * bs;
  struct base_struct * b;
  struct attribute_struct * a;

  printf("Reading data into g10\n");
  bs=bases;
  b=base_new();
  bs=dll_add(bs, b); //new file bas
  a=attribute_new("name", "files");
  b->attributes=dll_add(b->attributes, a);
  
  bases_read();
}
