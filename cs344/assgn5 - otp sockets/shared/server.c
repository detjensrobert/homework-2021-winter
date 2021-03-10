#include "server.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "debug.h"
#include "otp.h"
#include "socket.h"

int start_server(char *type, int port) {
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;

  socklen_t client_size = sizeof(client_addr);

  int connection_socket;

  // Create the socket that will listen for connections
  int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_socket < 0) {
    ERR("cannot open socket");
  }

  init_server_address_struct(&server_addr, port);

  if (bind(listen_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) < 0) {
    ERR("cannot bind socket");
  }

  listen(listen_socket, 5);  // allow 5 connections

  while (1) {
    // accept next waiting connection
    connection_socket =
        accept(listen_socket, (struct sockaddr *)&client_addr, &client_size);
    if (connection_socket < 0) {
      ERR("cannot accept connection");
    }

    dbg_printf("SERVER: Connected to client running at host %d port %d\n",
               ntohs(client_addr.sin_addr.s_addr), ntohs(client_addr.sin_port));

    dbg_printf("SERVER: Forking to handle connection...\n");
    // fork off process to handle accepted connection
    pid_t spawn_pid = fork();
    switch (spawn_pid) {
      case -1:
        ERR("cannot fork child");
        break;

      case 0:  // child
        handle_connection(connection_socket, type);
        dbg_printf("SERVER: connection finished, exiting child...\n");
        exit(0);
        break;

      default:;  // parent
        // close parent copy of connection
        close(connection_socket);

        // clean up any zombie children
        int child_status = 0;
        while (waitpid(-1, &child_status, WNOHANG))
          ;
        break;
    }
  }
}

void init_server_address_struct(struct sockaddr_in *address, int portNumber) {
  memset((char *)address, '\0', sizeof(*address));

  address->sin_family = AF_INET;
  address->sin_port = htons(portNumber);
  address->sin_addr.s_addr = INADDR_ANY;
}

void handle_connection(int socket_fd, char *accepted_type) {
  char conn_type[7];
  size_t payload_size = 0;

  // accept ident header
  recv(socket_fd, conn_type, 6, 0);

  // reject connections of wrong type
  if (strcmp(conn_type, accepted_type)) {
    dbg_printf("SERVER: invalid client\n");

    // send no-good message back and stop connection
    send(socket_fd, "NG", 3, 0);

    close(socket_fd);
    return;
  }
  send(socket_fd, "OK", 3, 0);

  // accept size field
  recv(socket_fd, &payload_size, sizeof(size_t), 0);

  dbg_printf("SERVER: Connected to client %s, size %zu\n", conn_type,
             payload_size);

  char *input = calloc(payload_size, sizeof(char));
  char *key = calloc(payload_size, sizeof(char));

  recv_full(socket_fd, input, payload_size, 0);
  recv_full(socket_fd, key, payload_size, 0);

  dbg_printf("SERVER: input: '%s'\n", input);
  dbg_printf("SERVER: key  : '%s'\n", key);

  // perform OTP
  char *output = otp_action(accepted_type, input, key, payload_size);

  // send result back
  send(socket_fd, output, payload_size, 0);
  dbg_printf("SERVER: outp : '%s'\n", output);

  free(input);
  free(key);
  free(output);

  close(socket_fd);
}
