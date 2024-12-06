#ifndef _NODE_
#define _NODE_

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include "structs.h"
#include "dll.h"
#include "attributes.h"
#include "relations.h"
#include "attribute.h"

extern long int swid;

struct dll * node_search_by_kv(struct dll *, char *, char *);
struct attribute_struct * node_get_attribute(struct dll *, char *);
int node_match_attribute(struct node_struct *, char *, char *);
struct node_struct * node_new();
void node_display(int, struct node_struct *);
struct node_struct * node_search_by_swid(struct base_struct *, long int);

#endif
