#include "client.h"

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "debug.h"

int start_client(char *type, char *input, char *key, size_t input_size,
                 int port) {
  struct sockaddr_in server_addr;

  // Create the socket that will listen for connections
  int connection_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (socket < 0) {
    ERR("cannot open socket");
  }

  init_client_address_struct(&server_addr, port, "localhost");

  // Connect to server
  if (connect(connection_socket, (struct sockaddr *)&server_addr,
              sizeof(server_addr)) < 0) {
    ERR("cannot connect to server");
  }

  // send text to server

  // header first
  send(connection_socket, type, strlen(type), 0);

  // get OK back?
  char status[3];
  recv(connection_socket, status, 3, 0);
  if (strcmp(status, "OK")) {
    // no good!
    ERR_ARG("invalid connection", 2);
  }

  send(connection_socket, &input_size, sizeof(size_t), 0);
  send(connection_socket, input, input_size, 0);
  send(connection_socket, key, input_size, 0);

  // get result back from server and print it
  char *result = calloc(input_size + 1, sizeof(char));
  recv(connection_socket, result, input_size, 0);
  printf("%s\n", result);
  free(result);

  return 0;
}

void init_client_address_struct(struct sockaddr_in *address, int port,
                                char *hostname) {
  // Clear out the address struct
  memset((char *)address, '\0', sizeof(*address));

  // The address should be network capable
  address->sin_family = AF_INET;
  // Store the port number
  address->sin_port = htons(port);

  // Get the DNS entry for this host name
  struct hostent *hostInfo = gethostbyname(hostname);
  if (hostInfo == NULL) {
    ERR("cannot find host");
  }
  // Copy the first IP address from the DNS entry to sin_addr.s_addr
  memcpy((char *)&address->sin_addr.s_addr, hostInfo->h_addr_list[0],
         hostInfo->h_length);
}

int validate_input(char *input, size_t len) {
  for (int i = 0; i < len - 1; i++) {
    // if not a valid char
    if (!(input[i] == ' ' || (input[i] >= 'A' && input[i] <= 'Z'))) {
      return 0;
    }
  }

  return 1;
}
