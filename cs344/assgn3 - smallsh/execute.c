#include "execute.h"

#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "debug.h"
#include "globals.h"
#include "parse.h"
#include "set.h"
#include "signals.h"

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

void builtin_status(int exitstatus) {
  if (WIFEXITED(exitstatus)) {
    printf("exit status %i\n", WEXITSTATUS(exitstatus));
  } else {
    printf("terminated by signal %i\n", WTERMSIG(exitstatus));
  }
}

int execute_command(struct Command *cmd, Set *bg_pids) {
  pid_t spawn_pid = fork();

  switch (spawn_pid) {
    case -1:
      perror("Error forking child");
      exit(1);
      break;

    case 0:  // child
      return execute_child(cmd);
      break;

    default:  // parent
      return execute_parent(cmd, spawn_pid, bg_pids);
      break;
  }

  return 0;
}

int execute_child(struct Command *cmd) {
  // set bg processes to /dev/null by default
  if (cmd->bg) {
    cmd->infile = cmd->infile ?: "/dev/null";
    cmd->outfile = cmd->outfile ?: "/dev/null";
  } else {
    // if not a bg process, use default SIGINT handler
    // (SIGINT ignored by default from parent process)
    default_sigint();
  }

  // all children should ignore SIGTSTP
  ignore_sigtstp();

  // open redirection files
  if (cmd->infile) {
    int infd = open(cmd->infile, O_RDONLY);

    if (infd == -1) {  // error opening file
      perror(cmd->infile);
      exit(1);
    }

    if (dup2(infd, 0) == -1) {
      perror("Error redirecting stdin");
      exit(2);
    }
  }

  if (cmd->outfile) {
    int outfd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0640);

    if (outfd == -1) {  // error opening file
      perror(cmd->outfile);
      exit(1);
    }

    if (dup2(outfd, 1) == -1) {
      perror("Error redirecting stdout");
      exit(2);
    }
  }

  execvp(cmd->command, cmd->argv);
  // exec only returns if error
  perror(cmd->command);
  exit(1);
}

int execute_parent(struct Command *cmd, int child_pid, Set *bg_pids) {
  int child_status;

  if (!cmd->bg) {  // command ran in foreground

    // wait for child process
    child_pid = waitpid(child_pid, &child_status, 0);

    // print message if terminated
    if (WIFSIGNALED(child_status)) {
      printf("terminated with signal %i\n", WTERMSIG(child_status));
    }
    return child_status;

  } else {
    printf("background pid is %i\n", child_pid);

    set_add(bg_pids, child_pid);
    return 0;
  }
}

int check_children(Set *bg_pids) {
  switch (bg_print_message) {
    case 1:
      printf("Entering foreground-only mode (& is now ignored)\n");
      break;
    case 2:
      printf("Exiting foreground-only mode\n");
      break;
  }
  bg_print_message = 0;

  LNode *walker = bg_pids->head;
  while (walker) {
    int child_status;
    int child_pid = waitpid(walker->val, &child_status, WNOHANG);

    switch (child_pid) {
      case -1:  // waitpid error
        perror("waitpid()");
        break;
      case 0:  // no process exited, noop
        break;
      default:  // process was exited, print its status
        printf("background pid %i is done: ", child_pid);
        builtin_status(child_status);
        set_remove(bg_pids, child_pid);
        break;
    }

    walker = walker->next;
  }

  return 1;
}
