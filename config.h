#ifndef _CONFIG_
#define _CONFIG_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "dll.h"
#include "attribute.h"
#include "node.h"

extern struct dll * config;

struct dll * config_init();

#endif
