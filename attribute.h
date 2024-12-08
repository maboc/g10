#ifndef _ATTRIBUTE_
#define _ATTRIBUTE_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "structs.h"
#include "dll.h"

extern long int swid;

void attribute_list(int, struct attribute_struct *);
struct attribute_struct * attribute_new(char *, char *);
void attribute_display(int s, struct attribute_struct *);

#endif
