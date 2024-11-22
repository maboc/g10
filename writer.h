#ifndef _WRITER_
#define _WRITER_

#include <stdio.h>
#include <pthread.h>
#include "structs.h"
#include "config.h"

extern int goon;
extern struct dll * bases;

void * writer(void *);
void * writer_start(void *);

#endif
