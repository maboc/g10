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

char * construct_file_name(char *, char *);
void bases_attributes_read();
void bases_read();
void reader();

#endif
