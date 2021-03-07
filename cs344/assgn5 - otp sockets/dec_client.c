#include <stdio.h>
#include <stdlib.h>

#define ENCODE_CLIENT

#include "shared/client.h"
#include "shared/debug.h"

int main(int argc, char **argv) {
  FILE *infile = NULL;
  FILE *keyfile = NULL;
  int port = 0;

  if (argc < 4) {
    fprintf(stderr, "Usage: dec_client <input_file> <key_file> <port>\n");
    ERR("missing required arguments");
  }

  infile = fopen(argv[1], "r");
  if (!infile) {
    ERR("cannot open input file");
  }

  keyfile = fopen(argv[2], "r");
  if (!keyfile) {
    ERR("cannot open key file");
  }

  port = atoi(argv[3]);
  if (port <= 0) {
    ERR("port must be a positive number");
  }

  char *input = NULL;
  size_t input_size = 0;
  char *key = NULL;
  size_t key_size = 0;

  input_size = getline(&input, &input_size, infile);
  key_size = getline(&key, &key_size, keyfile);

  // remove newline from strings
  input[--input_size] = '\0';
  key[--key_size] = '\0';

  dbg_printf("input (%zu): '%s'\n", input_size, input);
  dbg_printf("key (%zu): '%s'\n", key_size, key);

  if (!validate_input(input, input_size)) {
    ERR("invalid input file");
  }
  if (!validate_input(key, key_size)) {
    ERR("invalid key file");
  }
  if (key_size < input_size) {
    ERR("key is too small");
  }

  start_client("DECODE", input, key, input_size, port);

  free(input);
  free(key);

  fclose(infile);
  fclose(keyfile);
}
