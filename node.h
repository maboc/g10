#ifndef _NODE_
#define _NODE_

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include "structs.h"
#include "dll.h"
#include "attributes.h"
#include "relations.h"

extern long int swid;

struct node_struct * node_new();
void node_display(struct node_struct *);
struct node_struct * node_search_by_swid(struct base_struct *, long int);

#endif
