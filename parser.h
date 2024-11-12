#ifndef _PARSER_
#define _PARSER_

#include <string.h>
#include "structs.h"
#include "dll.h"

struct dll * commands_free(struct dll *);
char * commands_get_part(struct dll *, int);
char * remove_trailing_spaces(char *);
char * remove_leading_spaces(char *);
char * remove_mid_spaces(char *);
int commands_count(struct dll *);
struct dll * parse(char *);
  
#endif
