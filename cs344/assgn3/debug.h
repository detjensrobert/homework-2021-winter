#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#include "parse.h"
#include "set.h"

#define DEBUG 1
#define dbg_printf(format, ...)               \
  if (DEBUG) {                                \
    fprintf(stderr, (format), ##__VA_ARGS__); \
  }

void dbg_print_cmd(struct Command *cmd);

void dbg_print_set(Set *s);

#endif
