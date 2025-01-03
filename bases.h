#ifndef _BASES_
#define _BASES_

#include "structs.h"
#include "dll.h"
#include "base.h"
#include "attributes.h"

extern struct dll * bases;

struct base_struct * bases_search_on_id(int);
void bases_list(int);
void bases_display(int);
long int bases_count();

#endif
