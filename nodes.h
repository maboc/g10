#ifndef _NODES_
#define _NODES_

#include "structs.h"
#include "node.h"

struct dll * nodes_search(struct dll *, char *, char *);
void nodes_display(int, struct dll *);
long int nodes_count(struct dll *);

#endif
