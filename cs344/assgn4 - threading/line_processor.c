#include "processing.h"
#include "string_helpers.h"

void single_threaded() {
  char *input;

  while ((input = get_input())) {
    char *replaced = replace_separators(input);
    char *plussed = replace_plusses(replaced);
    print_output(plussed);
  }
}

int main(int argc, char **argv) {
  single_threaded();

  return 0;
}
