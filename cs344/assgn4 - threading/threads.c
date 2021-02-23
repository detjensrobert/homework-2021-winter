#include "threads.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "buffer.h"
#include "debug.h"
#include "processing.h"

struct buffer buffer12;
struct buffer buffer23;
struct buffer buffer34;

void multi_threaded() {
  buffer12 = buffer_create();
  buffer23 = buffer_create();
  buffer34 = buffer_create();

  buffer12.name = "\x1B[31m[inp->\x1B[33msep]\x1B[0m";
  buffer23.name = "\x1B[33m[sep->\x1B[34mpls]\x1B[0m";
  buffer34.name = "\x1B[34m[pls->\x1B[32mout]\x1B[0m";

  pthread_t input_t, separator_t, plus_t, print_t;

  pthread_create(&input_t, NULL, input_thread, NULL);
  pthread_create(&separator_t, NULL, separator_thread, NULL);
  pthread_create(&plus_t, NULL, plus_thread, NULL);
  pthread_create(&print_t, NULL, print_thread, NULL);

  // wait for threads to exit
  pthread_join(input_t, NULL);
  pthread_join(separator_t, NULL);
  pthread_join(plus_t, NULL);
  pthread_join(print_t, NULL);
}

void *input_thread() {
  struct buffer *outbuf = &buffer12;

  char *input;
  do {
    input = get_input();
    buffer_put_line(outbuf, input);
  } while (strcmp(input, "STOP\n"));

  dbg_printf("  ! got STOP in input thread\n");

  return NULL;
}

void *separator_thread() {
  struct buffer *inbuf = &buffer12;
  struct buffer *outbuf = &buffer23;

  char *input;
  do {
    input = buffer_get_line(inbuf);
    char *replaced = replace_separators(input);
    buffer_put_line(outbuf, replaced);
  } while (strcmp(input, "STOP\n"));

  dbg_printf("  ! got STOP in separator thread\n");

  return NULL;
}

void *plus_thread() {
  struct buffer *inbuf = &buffer23;
  struct buffer *outbuf = &buffer34;

  char *input;
  do {
    input = buffer_get_line(inbuf);
    char *replaced = replace_plusses(input);
    buffer_put_line(outbuf, replaced);
  } while (strcmp(input, "STOP "));

  dbg_printf("  ! got STOP in plus thread\n");

  return NULL;
}

void *print_thread() {
  struct buffer *inbuf = &buffer34;

  char *input;
  do {
    input = buffer_get_line(inbuf);
    print_output(input);
  } while (strcmp(input, "STOP "));

  dbg_printf("  ! got STOP in output thread\n");

  return NULL;
}
