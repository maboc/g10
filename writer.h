#ifndef _WRITER_
#define _WRITER_

#include <stdio.h>
#include <pthread.h>
#include "structs.h"
#include "config.h"

extern int goon;
extern struct dll * bases;

void write_node_attribute(struct base_struct *, struct node_struct *, struct attribute_struct *);
void process_node_attributes(struct base_struct *, struct node_struct *);
void write_node(struct base_struct *, struct node_struct *);
void process_node(struct base_struct *, struct node_struct *);
void process_nodes(struct base_struct *);
void write_base_attribute(struct base_struct *, struct attribute_struct *);
void process_base_attributes(struct base_struct *);
void write_base(struct base_struct *);
void process_base(struct base_struct *);
void process_bases(struct dll *);



void write_base(struct base_struct *);
void * writer(void *);
void * writer_start(void *);

#endif
