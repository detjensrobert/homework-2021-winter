#ifndef PARSE
#define PARSE

struct Command {
  char *command;
  char **args;
  int args_c;
  char *infile;
  char *outfile;
  int bg;
};

/**
  Parses the input line into a command, args, and i/o streams.

  @param  line  input string, must have some content
  @return Command struct containing parsed data
*/
struct Command *parse_command(char *line);

/**
  Completely frees all memory used in the input struct.

  @param  cmd   struct to be freed
*/
void free_command(struct Command *cmd);

/**
  Creates a new string with any leading and trailing whitespace from the input
  string removed. (whitespace being [ \n\t])

  @param  str   the string to be trimmed
  @return new string
*/
char *trim_whitespace(char *str);

#endif
