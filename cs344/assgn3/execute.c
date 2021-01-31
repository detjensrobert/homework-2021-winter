#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parse.h"

int validate_command(struct Command *cmd) {
  struct stat info;

  // open file descriptors here?

  // if file does not exist
  if (cmd->infile && (stat(cmd->infile, &info)) == -1) {
    fprintf(stderr, "ERR: input file %s not found\n", cmd->infile);
    return 1;
  }

  return 0;
}

int builtin_command(struct Command *cmd) {
  if (!strcmp(cmd->command, "status")) {
    return 1;
  }
  if (!strcmp(cmd->command, "cd")) {
    return 2;
  }
  if (!strcmp(cmd->command, "exit")) {
    return 3;
  }

  return 0;
}

int execute_command(struct Command *cmd) {

  int child_status;

  pid_t spawn_pid = fork();

  switch (spawn_pid) {
  case -1:
    perror("Error forking child");
    exit(1);
    break;

  case 0: // child
    execvp(cmd->command, cmd->argv);
    // exec only returns if error
    perror("Error executing command");
    exit(1);
    break;

  default: // parent

    if (!cmd->bg) { // command ran in foreground

      // wait for child process
      spawn_pid = waitpid(spawn_pid, &child_status, 0);

      // check return code
      if (WIFEXITED(child_status)) {
        return WEXITSTATUS(child_status);
      } else { // signaled
        return WTERMSIG(child_status);
      }

    } else {
      // add child pid to parent process
    }

    break;
  }

  return 0;
}
