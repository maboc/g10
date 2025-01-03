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
  struct control_struct * control;
};

struct node_struct{
  long int swid;
  struct dll * attributes;
  struct dll * relations;
  struct control_struct * control;
};

struct attribute_struct{
  long int swid;
  char * key;
  char * value;
  struct control_struct * control;
};

struct base_struct{
  long int swid;
  struct dll * attributes;
  struct dll * nodes;
  struct control_struct * control;
};

struct control_struct{
  int dirty;             //0: clean  1: dirty
  char * file;
  long int position;
  int status; // 0: nothing (or new) 1: update 2: delete
};

#endif
