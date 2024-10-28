#ifndef _DLL_
#define _DLL_

#include <stdlib.h>
#include <stddef.h>
#include "structs.h"

struct dll * dll_new();
struct dll * dll_add(struct dll *, void *);
struct dll * dll_last(struct dll *);
long int dll_count(struct dll *);
struct dll * dll_first(struct dll *);

#endif
