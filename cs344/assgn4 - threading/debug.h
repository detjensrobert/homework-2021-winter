#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#define DEBUG 0

#define dbg_printf(format, ...) \
  if (DEBUG) fprintf(stderr, (format), ##__VA_ARGS__)

#endif
