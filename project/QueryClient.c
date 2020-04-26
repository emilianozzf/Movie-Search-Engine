#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "QueryProtocol.h"

char *port_string = "1500";
unsigned short int port;
char *ip = "127.0.0.1";

#define BUFFER_SIZE 1000

void RunQuery(char *query) {
  // Find the address
  struct addrinfo hints, *infoptr;
  hints.ai_family = AF_INET; // AF_INET meas IPv4 only address
  hints.ai_socktype = SOCK_STREAM; // TCP

  int result = getaddrinfo(ip, port, &hints, &infoptr);
  if (result != 0) {
    printf("Could not get the address.\n");
    return;
  }
  
  // Create the socket
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    printf("Could not create the socket.\n");
    return;
  }

  // Connect to the server
  if (connect(socket_fd, infoptr->ai_addr, result->ai_addrlen) == -1) {
    printf("Could not connect!\n");
    return;
  }

  // Do the query-protocol
  char resp[1000];
  int len = read(socket_fd, resp, 999);
  resp[len] = '\0';
  if (CheckAck(resp) == -1) {
    printf("Did not receive ACK.\n");
    return;
  }

  write(socket_fd, input, strlen(input));
  int len = read(socket_fd, resp, 999);
  resp[len] = '\0';
  int num_of_responses = atoi(resp);
  SendAck(socket_fd);
  for (int i = 0; i < num_of_responses; i ++) {
    int len = read(socket_fd, resp, 999);
    resp[len] = '\0';
    printf("%s\n", resp);
    SendAck(socket_fd);
  }

  int len = read(socket_fd, resp, 999);
  resp[len] = '\0';
  if (CheckGoodbye(resp) == 0) {
    freeaddrinfo(infoptr);
    close(socket_fd);
    return;
  }

  // Close the connection
}

void RunPrompt() {
  char input[BUFFER_SIZE];

  while (1) {
    printf("Enter a term to search for, or q to quit: ");
    scanf("%s", input);

    printf("input was: %s\n", input);

    if (strlen(input) == 1) {
      if (input[0] == 'q') {
        printf("Thanks for playing! \n");
        return;
      }
    }
    printf("\n\n");
    RunQuery(input);
  }
}

// This function connects to the given IP/port to ensure 
// that it is up and running, before accepting queries from users.
// Returns 0 if can't connect; 1 if can. 
int CheckIpAddress(char *ip, char *port) {
  // Connect to the server

  // Resolves DNS names
  struct addrinfo hints, *infoptr;
  hints.ai_family = AF_INET; // AF_INET meas IPv4 only address
  hints.ai_socktype = SOCK_STREAM; // TCP

  int result = getaddrinfo(ip, port, &hints, &infoptr);
  if (result != 0) {
    printf("Could not get the address.\n");
    return 0;
  }

  // Creates a socket
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    printf("Could not create the socket.\n");
    return 0;
  }

  if (connect(socket_fd, infoptr->ai_addr, result->ai_addrlen) == -1) {
    printf("Could not connect!\n");
    return 0;
  }

  // Listen for an ACK
  char resp[1000];
  int len = read(socket_fd, resp, 999);
  resp[len] = '\0';
  if (CheckAck(resp) == -1) {
    printf("Did not receive ACK.\n");
    return 0;
  }

  // Sends a GOODBYE
  if (SendGoodbye(socket_fd) == -1) {
    printf("Did not send GOODBYE!\n");
    return 0;
  }  

  // Closes the connection
  freeaddrinfo(infoptr);
  close(socket_fd);
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Incorrect number of arguments. \n");
    printf("Correct usage: ./queryclient [IP] [port]\n");
    return 1;
  } else {
    ip = argv[1];
    port_string = argv[2];
  }

  if (CheckIpAddress(ip, port_string)) {
    RunPrompt();
  }
  return 0;
}
