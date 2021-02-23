#include "processing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_helpers.h"

char* get_input() {
  char* input = NULL;
  size_t input_size = 0;

  input_size = getline(&input, &input_size, stdin);

  if (input_size == -1) {  // catch EOF, etc
    perror("getline()");
    exit(1);
  }

  return input;
}

char* replace_separators(char* input) {
  return string_replace(input, "\n", " ");
}

char* replace_plusses(char* input) { return string_replace(input, "++", "^"); }

char printbuffer[80] = "";
int printbuffer_idx = 0;

void print_output(char* input) {
  for (int i = 0; i < strlen(input); i++) {
    printbuffer[printbuffer_idx] = input[i];
    printbuffer_idx++;

    if (printbuffer_idx >= 80) {
      printf("%.80s\n", printbuffer);
      printbuffer_idx = 0;
    }
  }
}
