#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debug.h"
#include "globals.h"

struct Command *parse_command(char *line) {
  struct Command *cmd = calloc(1, sizeof(struct Command));

  char *token = NULL;
  char *t_saveptr = NULL;

  // replace all $$ with current pid
  char pidstr[10];
  sprintf(pidstr, "%i", getpid());
  char *expandedline = string_replace(line, "$$", pidstr);

  // is last arg a &?
  if (expandedline[strlen(expandedline) - 1] == '&') {
    cmd->bg = 1;
    expandedline[strlen(expandedline) - 1] = '\0';  // remove & from str
  }

  // parse command as first arg
  token = strtok_r(expandedline, " ", &t_saveptr);
  while (token) {
    switch (token[0]) {
      case '<':  // input redirection
        token = strtok_r(NULL, " ", &t_saveptr);
        cmd->infile = calloc(strlen(token) + 1, sizeof(char));
        strcpy(cmd->infile, token);
        break;

      case '>':  // output redirection
        token = strtok_r(NULL, " ", &t_saveptr);
        cmd->outfile = calloc(strlen(token) + 1, sizeof(char));
        strcpy(cmd->outfile, token);
        break;

      default:  // parse as arg
        cmd->argv = realloc(cmd->argv, sizeof(char *) * (cmd->argc + 2));
        cmd->argv[cmd->argc] = calloc(strlen(token) + 1, sizeof(char));
        strcpy(cmd->argv[cmd->argc], token);
        cmd->argc++;
        cmd->argv[cmd->argc] = NULL;  // keep null ptr at end of arr
    }

    token = strtok_r(NULL, " ", &t_saveptr);
  }

  free(expandedline);

  cmd->command = cmd->argv[0];
  cmd->bg = cmd->bg & bg_allowed;
  return cmd;
}

void free_command(struct Command *cmd) {
  // free(cmd->command);
  for (int i = 0; i < cmd->argc; i++) {
    free(cmd->argv[i]);
  }
  free(cmd->argv);
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

  char *trimmed = calloc(end - start + 2, sizeof(char));
  str[end + 1] = '\0';  // add null term in correct place
  strcpy(trimmed, str + start);

  return trimmed;
}

char *string_replace(char *str, char *from, char *to) {
  char *substr_pos = str;

  // count # of froms in str
  int sub_count = 0;
  int from_len = strlen(from);
  while ((substr_pos = strstr(substr_pos, from))) {
    sub_count++;
    substr_pos += from_len;  // avoid overlaps
  }

  // alloc new string with room for replacements
  int len_diff = (strlen(to) - from_len);
  char *replaced = calloc(strlen(str) + len_diff * sub_count + 1, sizeof(char));

  if (sub_count) {  // replace all instances of from with to
    substr_pos = str;

    while ((substr_pos = strstr(substr_pos, from))) {
      // copy orig str up to `from`
      strncat(replaced, str, (substr_pos - str));
      strcat(replaced, to);  // replace with `to`

      substr_pos += from_len;  // avoid overlaps
      str = substr_pos;
    }

    if (str < str + strlen(str)) {  // copy rest of orig string
      strcat(replaced, str);
    }

  } else {  // no replacements needed, just copy original string
    strcpy(replaced, str);
  }

  return replaced;
}
