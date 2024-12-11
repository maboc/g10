#ifndef _READER_
#define _READER_

#include <stdio.h>
#include "config.h"
#include "base.h"
#include "node.h"
#include "attributes.h"
#include "relation.h"
#include "structs.h"

extern struct dll * bases;

void file_in_administration(char *, char *);
char * construct_file_name(char *, char *);
void nodes_attributes_read();
void nodes_read();
void bases_attributes_read();
void bases_read();
void reader();

#endif
