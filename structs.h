#ifndef _STRUCTS_
#define _STRUCTS_

struct dll{
  struct dll * prev;
  struct dll * next;
  void * payload;
};

struct relation_struct{
  long int swid;
  struct node_struct * node_to;
  struct dll * attributes;
};

struct node_struct{
  long int swid;
  struct dll * attributes;
  struct dll * relations;
};

struct attribute_struct{
  long int swid;
  char * key;
  char * value;
};

struct base_struct{
  long int swid;
  struct dll * attributes;
  struct dll * nodes;
};

struct config_struct{
  int data_writer_interval;
  char * data_dir;
};
#endif
