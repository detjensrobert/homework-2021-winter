#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debug.h"
#include "execute.h"
#include "parse.h"

int main(int argc, char *argv[]) {

  char *line = NULL;
  size_t line_length = 0;

  int want_exit = 0;
  int exitstatus = 0;

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
    struct Command *cmd = parse_command(trimmed);

    // dbg_print_cmd(cmd);

    // handle builtins
    switch (builtin_command(cmd)) {
    case 1:; // status
      printf("exit value %i\n", exitstatus);
      break;

    case 2:; // cd
      if (cmd->argc > 1) {
        chdir(cmd->argv[1]);
      } else {
        chdir(getenv("HOME"));
      }
      break;

    case 3: // exit
      want_exit = 1;
      break;

    default: // not a builtin
      exitstatus = execute_command(cmd);
    }

    // cleanup
    free_command(cmd);
    free(trimmed);
  }

  // dbg_printf("  > bye\n");
  free(line);
}
