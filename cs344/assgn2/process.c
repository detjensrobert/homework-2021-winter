#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include "movies.h"
#include "process.h"

int process_movies(struct Movie *movies) {

  // create dir $ONID.movies.$RAND[0..99999]
  srand(time(NULL));

  char *dirname = malloc(sizeof(char) * 22);
  sprintf(dirname, "detjensr.movies.%i", rand() % 100000);

  mkdir(dirname, 0750); // rwx r-x ---

  printf("Created directory with name %s\n", dirname);

  // add movie titles released in $YEAR to $YEAR.txt
  FILE *yearfile = NULL;

  struct Movie *walker = movies;
  while (walker != NULL) {
    char* filename = malloc(sizeof(char) * 32);
    sprintf(filename, "%s/%i.txt", dirname, walker->year);

    yearfile = fopen(filename, "a");

    fprintf(yearfile, "%s\n", walker->title);

    fclose(yearfile);
    chmod(filename, 0640); // rw- r-- ---

    free(filename);
    walker = walker->next;
  }

  free(dirname);
  return 0;
}
