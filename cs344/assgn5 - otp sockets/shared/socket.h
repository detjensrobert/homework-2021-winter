#include <sys/socket.h>
#include <sys/types.h>

#define CHUNK_SIZE 1000

int min(int a, int b);

ssize_t send_full(int socket, char* buffer, size_t length, int flags);
ssize_t recv_full(int socket, char* buffer, size_t length, int flags);
