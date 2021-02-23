#ifndef BUFFER
#define BUFFER

#include <pthread.h>

#define BUFFER_SIZE 50
#define BUFFER_LENGTH 1000

struct buffer {
  int count;
  int prod_idx;
  int cons_idx;
  char *name;
  pthread_mutex_t mutex;
  pthread_cond_t has_data;
  char buffer[BUFFER_SIZE][BUFFER_LENGTH];
};

struct buffer buffer_create();

void buffer_put_line(struct buffer *b, char *line);
char *buffer_get_line(struct buffer *b);

#endif
