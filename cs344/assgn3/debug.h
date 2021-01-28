#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include "parse.h"

#define DEBUG 1
#define dbg_printf(str, ...)                                                   \
  if (DEBUG) {                                                                 \
    fprintf(stderr, (str), ##__VA_ARGS__);                                     \
  }

void dbg_print_cmd(struct Command *cmd);

#endif
