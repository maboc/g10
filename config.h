#ifndef _CONFIG_
#define _CONFIG_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "dll.h"
#include "attribute.h"
#include "node.h"
#include "base.h"
#include "parser.h"
#include "logging.h"

extern struct dll * bases;

char * config_get_char(char *);
int config_get_int(char *);
struct dll * config_init(void);

#endif
