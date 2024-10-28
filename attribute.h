#ifndef _ATTRIBUTE_
#define _ATTRIBUTE_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "dll.h"

extern long int swid;

struct attribute_struct * attribute_new(char *, char *);
void attribute_display(struct attribute_struct *);

#endif
