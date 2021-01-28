#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "parse.h"

int main(int argc, char *argv[]) {

  char *line = NULL;
  size_t line_length = 0;

  int want_exit = 0;

  while (!want_exit && printf(": ") &&
         getline(&line, &line_length, stdin) != -1) {

    // ignore comments
    if (line[0] == '#') {
      // dbg_printf("  > got comment\n");
      continue;
    }

    char *trimmed = trim_whitespace(line);
    line_length = strlen(trimmed);

    // dbg_printf("  > trimmed: '%s' (%li)\n", trimmed, line_length);

    // ignore blank lines
    if (line_length == 0) {
      // dbg_printf("  > got blank line\n");
      continue;
    }

    // parse line
    struct Command *cmd = parse_command(line);

    // execute command

    // cleanup
    free_command(cmd);
    free(trimmed);
  }

  dbg_printf("\n  > bye\n");
  free(line);
}
