#ifndef _HANDLER_
#define _HANDLER_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "output.h"
#include "structs.h"
#include "parser.h"
#include "bases.h"

extern int goon;

void * handler(void * data_in);

#endif
