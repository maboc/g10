#ifndef _RELATION_
#define _RELATION_

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "attributes.h"

extern long int swid;

struct relation_struct * relation_new(struct node_struct *);
void relation_display(int, struct relation_struct *);

#endif
