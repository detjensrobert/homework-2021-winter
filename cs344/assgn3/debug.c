#include "debug.h"

void dbg_print_cmd(struct Command *cmd) {
  dbg_printf("  > command parsed:\n");
  dbg_printf("  >   cmd: '%s'\n", cmd->command);
  dbg_printf("  >  argc: %i\n", cmd->argc);
  dbg_printf("  >  argv:");
  for (int i = 0; i < cmd->argc; i++) {
    dbg_printf(" '%s'", cmd->argv[i]);
  }
  dbg_printf("\n  >   inf: %s\n", cmd->infile);
  dbg_printf("  >  outf: %s\n", cmd->outfile);
  dbg_printf("  >   bg?: %i\n", cmd->bg);
}
