#ifndef _CONFIG_
#define _CONFIG_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"

extern struct config_struct * config;

struct config_struct * config_read();

#endif
