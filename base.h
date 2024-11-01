#ifndef _BASE_
#define _BASE_

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "dll.h"
#include "attributes.h"
#include "node.h"
#include "nodes.h"

extern struct dll * bases;
extern long int swid;

struct base_struct * base_new();
void base_display(struct base_struct *);
struct base_struct * base_search_by_swid(long int);

#endif
