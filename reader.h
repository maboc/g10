#ifndef _READER_
#define _READER_

#include <stdio.h>
#include "config.h"
#include "base.h"
#include "node.h"
#include "attributes.h"
#include "relation.h"
#include "structs.h"

extern struct dll * bases;

void bases_read();
void reader();

#endif
