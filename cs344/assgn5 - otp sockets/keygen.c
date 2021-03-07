#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

int main(int argc, char **argv) {
  int length = 0;

  if (argc < 2) {
    fprintf(stderr, "ERR: missing required argument\n");
    fprintf(stderr, "Usage: keygen <length>\n");
    exit(1);
  }

  length = atoi(argv[1]);

  if (length <= 0) {
    fprintf(stderr, "ERR: length must be a positive number\n");
    fprintf(stderr, "Usage: keygen <length>\n");
    exit(1);
  }

  srand(time(0));

  for (int i = 0; i < length; i++) {
    putc(alphabet[rand() % 27], stdout);
  }
  putc('\n', stdout);
}
