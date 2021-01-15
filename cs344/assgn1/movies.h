#ifndef MOVIES
#define MOVIES

struct Movie {
  char *title;
  int year;
  char **langs;
  int lang_count;
  float rating;
  struct Movie *next;
};

struct Movie *movies_parse(char *filename);
struct Movie *movies_create(char *line);
int movies_count(struct Movie *movies);
void movies_delete(struct Movie *movies);

#endif
