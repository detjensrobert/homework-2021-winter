#ifndef THREADS
#define THREADS

#include "buffer.h"

void multi_threaded();

void *input_thread();
void *separator_thread();
void *plus_thread();
void *print_thread();

#endif
