#include <stdio.h>
#include <stdlib.h>

#include "shared/debug.h"
#include "shared/server.h"

int main(int argc, char **argv) {
  int port = 0;

  if (argc < 2) {
    fprintf(stderr, "Usage: dec_server <port>\n");
    ERR("missing required arguments");
  }

  port = atoi(argv[1]);
  if (port <= 0) {
    ERR("port must be a positive number");
  }

  start_server("DECODE", port);
}
