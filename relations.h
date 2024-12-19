#ifndef _RELATIONS_
#define _RELATIONS_

#include <stdio.h>
#include "structs.h"
#include "dll.h"
#include "relation.h"

int relations_search_2(struct dll *, char *, char *);
struct dll * relations_search(struct dll *, char *, char *);
void relations_display(int, struct dll *);
long int relations_count(struct dll *);

#endif
