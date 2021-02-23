#include "processing.h"
#include "string.h"
#include "threads.h"

void single_threaded() {
  char *input = get_input();

  while (strcmp(input, "STOP\n")) {
    char *replaced = replace_separators(input);
    char *plussed = replace_plusses(replaced);
    print_output(plussed);
    input = get_input();
  }
}

int main(int argc, char **argv) {
  // single_threaded();

  multi_threaded();

  return 0;
}
