#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "parse.h"

struct Command *parse_command(char *line) {
  struct Command *cmd = malloc(sizeof(struct Command));

  char *token = NULL;
  char *t_saveptr = NULL;

  // set defaults
  cmd->args = NULL;
  cmd->args_c = 0;
  cmd->infile = NULL;
  cmd->outfile = NULL;
  cmd->bg = 0;

  // parse command as first arg
  token = strtok_r(line, " ", &t_saveptr);
  cmd->command = calloc(strlen(token) + 1, sizeof(char));
  strcpy(cmd->command, token);

  while ((token = strtok_r(NULL, " ", &t_saveptr))) {

    switch (token[0]) {
    case '<': // input redirection
      token = strtok_r(NULL, " ", &t_saveptr);
      cmd->infile = calloc(strlen(token) + 1, sizeof(char));
      strcpy(cmd->infile, token);
      break;

    case '>': // output redirection
      token = strtok_r(NULL, " ", &t_saveptr);
      cmd->outfile = calloc(strlen(token) + 1, sizeof(char));
      strcpy(cmd->outfile, token);
      break;

    case '&': // run in background
      cmd->bg = 1;
      break;

    default:; // parse as arg
      cmd->args = realloc(cmd->args, sizeof(char *) * (cmd->args_c + 1));
      cmd->args[cmd->args_c] = malloc(sizeof(char) * (strlen(token) + 1));
      strcpy(cmd->args[cmd->args_c], token);
      cmd->args_c++;
    }
  }

  return cmd;
}

void free_command(struct Command *cmd) {
  free(cmd->command);

  for (int i = 0; i < cmd->args_c; i++) {
    free(cmd->args[i]);
  }
  free(cmd->args);
  free(cmd->infile);
  free(cmd->outfile);
  free(cmd);
}

char *trim_whitespace(char *str) {
  int start = 0;
  int end = strlen(str);

  // consume start whitespace
  while (start < end &&
         (str[start] == ' ' || str[start] == '\n' || str[start] == '\t')) {
    start++;
  }

  // consume end whitespace
  while (end > start && (str[end] == ' ' || str[end] == '\n' ||
                         str[end] == '\t' || str[end] == '\0')) {
    end--;
  }

  char *trimmed = malloc(sizeof(char) * (end - start + 2));
  str[end + 1] = '\0'; // add null term in correct place
  strcpy(trimmed, str + start);

  return trimmed;
}
