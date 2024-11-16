#include <stdio.h>
#include "structs.h"
#include "dll.h"
#include "attribute.h"
#include "node.h"
#include "base.h"
#include "bases.h"
#include "relation.h"
#include "relations.h"
#include "data.h"
#include "listener.h"
#include "config.h"

struct dll * config=NULL;
long int swid=0; /*System Wide ID*/
struct dll * bases=NULL;
int goon=0;
