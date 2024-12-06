#include "reader.h"

void bases_read() {
  char * file_name;
  char * dir_name;
  char * totaal;
  char * tmp;
  struct dll * bs;
  struct base_struct * b;
  FILE * fp;
  unsigned long int file_size=0;
  struct node_struct * n;
  struct attribute_struct * a;
  long int position;
  char * buffer=NULL;
  long int base_id;
  
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

    //now comes the heavy lifting : reading from the file into bases

    //first determine lenth
    fseek(fp, 0, SEEK_END);
    file_size=ftell(fp);
    for(position=0; position<=file_size-sizeof(long int); position=position+sizeof(long int)){
      fseek(fp, position, SEEK_SET);
      fread(&base_id, sizeof(long int), 1, fp);
      if (base_id!=0){
	printf("Position : %i Base id %i\n", position, base_id);
	struct base_struct * b;

	b=base_new(base_id);
	b->control->file=malloc(strlen(totaal)+1);
	bzero(b->control->file, strlen(totaal)+1);
	b->control->file=strncpy(b->control->file, totaal, strlen(totaal));
	b->control->position=position;
	bs=dll_add(bs, b);
      }
    }
    fclose(fp);
  } else {
    printf("Create basefile : %s\n", totaal);

    //create the actual file
    fp=fopen(totaal, "w+");

    //initialize a buffer to write to the new file
    buffer=malloc(2048);
    bzero(buffer, 2048);

    fwrite(buffer, 2048, 1, fp);
    fflush(fp);
    fclose(fp);

    file_size=2*1024;
  }
    
  // CReate the file in the administration
  n=node_new();
  b=base_search_by_kv("name","files");
  b->nodes=dll_add(b->nodes, n);
  a=attribute_new("name", totaal);
  n->attributes=dll_add(n->attributes, a);
  a=attribute_new("type", "bases");
  n->attributes=dll_add(n->attributes, a);

  tmp=malloc(100);
  bzero(tmp, 100);

  sprintf(tmp, "%i", file_size);
  a=attribute_new("file_size", tmp);
  n->attributes=dll_add(n->attributes, a);
  
  free(tmp);  
  free(totaal);
}

void reader() {
  struct dll * bs;
  struct base_struct * b;
  struct attribute_struct * a;

  printf("Reading data into g10\n");
  bs=bases;
  b=base_new(0);
  bs=dll_add(bs, b); //new file bas
  a=attribute_new("name", "files");
  b->attributes=dll_add(b->attributes, a);
  
  bases_read();
}
