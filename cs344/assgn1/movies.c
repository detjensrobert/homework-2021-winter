#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movies.h"

/*
 * Reads the given filename and creates a linked list of movies.
 */
struct Movie *movies_parse(char *filename) {

  FILE *infile = fopen(filename, "r");

  if (infile == NULL) {
    fprintf(stderr, "Error opening file!\n");
    exit(1);
  }

  struct Movie *head = NULL;
  struct Movie *tail = NULL;

  char *line = NULL;
  size_t line_length = 0;

  // discard header row
  getline(&line, &line_length, infile);

  while (getline(&line, &line_length, infile) != -1) {

    struct Movie *new = movies_create(line);

    if (head == NULL) { // first node?
      head = new;
      tail = new;
    } else {
      tail->next = new;
      tail = new;
    }
  }

  free(line);
  fclose(infile);
  return head;
}

/*
 * Parses the passed line and creates a Movie struct
 */
struct Movie *movies_create(char *line) {

  struct Movie *m = malloc(sizeof(struct Movie));
  char *saveptr = NULL;

  // get movie title
  char *token = strtok_r(line, ",", &saveptr);
  m->title = calloc(strlen(token) + 1, sizeof(char));
  strcpy(m->title, token);

  // get year
  token = strtok_r(NULL, ",", &saveptr);
  m->year = atoi(token);

  // get list of langs
  token = strtok_r(NULL, ",", &saveptr);
  // parse list into array
  m->lang_count = 0;
  m->langs = malloc(sizeof(char *) * m->lang_count);
  char *lang_saveptr = NULL;
  char *lang_token = strtok_r(token, "[;]", &lang_saveptr);
  do {
    m->langs = realloc(m->langs, sizeof(char *) * (m->lang_count + 1));
    m->langs[m->lang_count] = calloc(strlen(lang_token) + 1, sizeof(char));
    strcpy(m->langs[m->lang_count], lang_token);
    m->lang_count++;
  } while ((lang_token = strtok_r(NULL, "[;]", &lang_saveptr)) != NULL);

  // get rating
  token = strtok_r(NULL, ",", &saveptr);
  m->rating = atof(token);

  m->next = NULL;

  return m;
}

/*
 * Counts the number of movies in the given linked list
 */
int movies_count(struct Movie *movies) {
  int count = 0;
  struct Movie *walker = movies;

  while (walker != NULL) {
    walker = walker->next;
    count++;
  }

  return count;
}

/*
 * Frees the linked list
 */
void movies_delete(struct Movie *m) {
  struct Movie *next = NULL;

  while (m != NULL) {
    next = m->next;
    free(m->title);
    for (int i = 0; i < m->lang_count; i++) {
      free(m->langs[i]);
    }
    free(m->langs);
    free(m);
    m = next;
  }
}
