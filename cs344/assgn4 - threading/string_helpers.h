#ifndef STRING_HELPERS
#define STRING_HELPERS

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
