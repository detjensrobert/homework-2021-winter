#include "otp.h"

#include <stdlib.h>

char *otp_action(char *type, char *input, char *key, int length) {
  switch (type[0]) {
    case 'E':
      return otp_encode(input, key, length);
    case 'D':
      return otp_decode(input, key, length);
    default:
      return NULL;
  }
}

char *otp_encode(char *input, char *key, int length) {
  char *output = calloc(length, sizeof(char));

  for (int i = 0; i < length; i++) {
    output[i] = int_to_char((char_to_int(input[i]) + char_to_int(key[i])) % 27);
  }

  return output;
}

char *otp_decode(char *input, char *key, int length) {
  char *output = calloc(length, sizeof(char));

  for (int i = 0; i < length; i++) {
    output[i] = int_to_char((char_to_int(input[i]) - char_to_int(key[i])) % 27);
  }

  return output;
}

int char_to_int(char c) {
  if (c == ' ') {
    return 0;
  } else {
    return c - 'A' + 1;
  }
}

char int_to_char(int i) {
  if (i < 0) i += 27;
  return " ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i];
}
