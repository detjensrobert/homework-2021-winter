#include <stdio.h>
#include <stdlib.h>

#include "analysis.h"
#include "movies.h"

int main(int argc, char *argv[]) {
  char *filename = argv[1];

  struct Movie *movies = movies_parse(filename);
  int count = movies_count(movies);

  printf("Processed file %s and parsed data for %i movies\n", filename,
         count);

  do_analysis(movies);

  movies_delete(movies);
}
