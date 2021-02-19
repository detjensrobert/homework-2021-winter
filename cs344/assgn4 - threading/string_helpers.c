#include <stdlib.h>
#include <string.h>

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
