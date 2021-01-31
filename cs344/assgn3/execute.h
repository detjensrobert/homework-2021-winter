#ifndef EXECUTE
#define EXECUTE

#include "parse.h"

/**
  Returns whether the command is a builtin.

  @param  cmd   command to validate
  @return 0 if not, 1 if status, 2 if cd, 3 if exit
*/
int builtin_command(struct Command *cmd);

/**
  Executes the command detailed by `cmd`.

  @param  cmd   command to execute
  @return the exit status of cmd
*/
int execute_command(struct Command *cmd);

/**
  Validates the given command:
  - input file exists (if set)

  @param  cmd   command to validate
  @return 1 (true) if passed, 0 (false) if failed
*/
int validate_command(struct Command *cmd);

#endif
