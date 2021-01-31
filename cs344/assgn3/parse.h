#ifndef PARSE
#define PARSE

struct Command {
  char *command;
  int argc;
  char **argv;
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
  @return new string with whitespace removed
*/
char *trim_whitespace(char *str);

/**
  Creates a new string with all instances of `from` in the input string `str`
  replaced with `to`.

  @param  str   the string to modify
  @param  from  substring to replace
  @param  to    string to replace `from` with
  @return the new string with replacements
*/
char *string_replace(char *str, char *from, char *to);

#endif
