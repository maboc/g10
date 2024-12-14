#ifndef _LISTENER_
#define _LISTENER_

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include "handler.h"
#include "logging.h"

extern int goon;

void * listener_start(void *);

#endif
