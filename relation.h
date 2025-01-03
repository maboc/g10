#ifndef _RELATION_
#define _RELATION_

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "attributes.h"

extern long int swid;

int relation_search(struct dll *, char *, char *);
struct relation_struct * relation_search_by_swid(struct node_struct *, int);
struct relation_struct * relation_new(long int, struct node_struct *);
void relation_display(int, struct relation_struct *);

#endif
