#include <netinet/in.h>
#include <stdio.h>

#define BUFFER_SIZE 256

int start_server(char *type, int port);

void init_server_address_struct(struct sockaddr_in *address, int portNumber);
void handle_connection(int socket_fd, char *accepted_type);
