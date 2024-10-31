#ifndef _PARSER_
#define _PARSER_

#include <string.h>
#include "structs.h"
#include "dll.h"

char * commands_get_part(struct dll *, int);
char * remove_leading_spaces(char *);
struct dll * parse(char *);
  
#endif
