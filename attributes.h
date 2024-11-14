#ifndef _ATTRIBUTES_
#define _ATTRIBUTES_

#include <stdio.h>
#include <unistd.h>
#include "structs.h"
#include "dll.h"
#include "attribute.h"

void attributes_list(int, struct dll *);
void attributes_display(int, struct dll *);
long int attributes_count(struct dll *);

#endif
