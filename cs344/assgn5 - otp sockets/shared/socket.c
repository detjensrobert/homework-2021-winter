#include "socket.h"

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "debug.h"

int min(int a, int b) { return a < b ? a : b; }

ssize_t send_full(int socket, char *buffer, size_t length, int flags) {
  ssize_t total_sent = 0;
  char *current = buffer;

  do {
    dbg_printf("  sending %i bytes out of %zu total...\n",
               min(length - total_sent, CHUNK_SIZE), length);

    ssize_t bytes_sent =
        send(socket, current, min(length - total_sent, CHUNK_SIZE), 0);
    total_sent += bytes_sent;
    current += bytes_sent;
  } while (total_sent < length);

  return total_sent;
}

ssize_t recv_full(int socket, char *buffer, size_t length, int flags) {
  ssize_t total_received = 0;
  char *current = buffer;

  do {
    dbg_printf("  receiving %i bytes out of %zu total...\n",
               min(length - total_received, CHUNK_SIZE), length);

    ssize_t bytes_received =
        recv(socket, current, min(length - total_received, CHUNK_SIZE), 0);
    total_received += bytes_received;
    current += bytes_received;
  } while (total_received < length);

  return total_received;
}
