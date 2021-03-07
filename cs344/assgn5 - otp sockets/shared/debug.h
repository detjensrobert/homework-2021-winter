#ifndef DEBUG_H
#define DEBUG_H

#include <errno.h>
#include <stdio.h>

#define DEBUG 0

#define dbg_printf(format, ...) \
  if (DEBUG) fprintf(stderr, (format), ##__VA_ARGS__)

#define ERR(msg) ERR_ARG(msg, 1)

#define ERR_ARG(msg, code)                            \
  fprintf(stderr, "[ \e[1;31mERR\e[0;37m ] %s", msg); \
  if (errno)                                          \
    perror(" ");                                      \
  else                                                \
    fputc('\n', stderr);                              \
  exit(code)

#endif
