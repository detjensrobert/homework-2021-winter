#include "buffer.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

struct buffer buffer_create() {
  struct buffer b = {
      0, 0, 0, NULL, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};
  return b;
}

// buffer put/get implementations adapted from
// [sample program](https://repl.it/@cs344/65prodconspipelinec)

void buffer_put_line(struct buffer *b, char *line) {
  dbg_printf("    > storing '%s' into buffer %s\n", line, b->name);

  pthread_mutex_lock(&b->mutex);  // lock buffer

  // add line to buffer while locked
  strncpy(b->buffer[b->prod_idx], line, BUFFER_LENGTH);
  b->prod_idx++;
  b->count++;

  pthread_cond_signal(&b->has_data);  // signal there is now data to read

  pthread_mutex_unlock(&b->mutex);  // unlock buffer once done
}

char *buffer_get_line(struct buffer *b) {
  dbg_printf("    < reading line from buffer %s\n", b->name);
  char *line = NULL;

  pthread_mutex_lock(&b->mutex);  // lock buffer

  // wait for data
  while (b->count == 0) {
    pthread_cond_wait(&b->has_data, &b->mutex);
  }

  // extract line from buffer
  line = calloc(BUFFER_LENGTH, sizeof(char));
  strncpy(line, b->buffer[b->prod_idx], BUFFER_LENGTH);
  b->cons_idx++;
  b->count--;

  pthread_mutex_unlock(&b->mutex);  // unlock buffer once done
  dbg_printf("    < got '%s' line from buffer %s\n", line, b->name);

  return line;
}
