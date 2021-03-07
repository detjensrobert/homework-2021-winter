#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>

int start_client(char *type, char *input, char *key, size_t input_size,
                 int port);

void init_client_address_struct(struct sockaddr_in *address, int port,
                                char *hostname);

/**
  Returns true if the given string has only valid characters [A-Z ]
*/
int validate_input(char *input, size_t len);
