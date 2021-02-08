#ifndef EXECUTE
#define EXECUTE

#include "parse.h"
#include "set.h"

/**
  Returns whether the command is a builtin.

  @param  cmd   command to validate
  @return 0 if not, 1 if status, 2 if cd, 3 if exit
*/
int builtin_command(struct Command *cmd);

/**
  Prints message to stdout based on `exitstatus`.
  @param  exitstatus  the status returned by waitpid()
  @return nothing, prints to stdout
*/
void builtin_status(int exitstatus);

/**
  Executes the command detailed by `cmd`.

  @param  cmd   command to execute
  @return the exit status of cmd
*/
int execute_command(struct Command *cmd, Set *bg_pids);

int execute_child(struct Command *cmd);
int execute_parent(struct Command *cmd, int child_pid, Set *bg_pids);

/**
  Iterates over the given list of children to check status of.
  Also prints any signal messages.
*/
int check_children(Set *bg_pids);

#endif
