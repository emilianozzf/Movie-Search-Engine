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

int do_connect() {
  int s;
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  struct addrinfo hints, *result;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET; /* IPv4 only */
  hints.ai_socktype = SOCK_STREAM; /* TCP */
  s = getaddrinfo(ip, port_string, &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(1);
  }

  if (connect(sock_fd, result->ai_addr, result->ai_addrlen) == -1) {
    perror("connect");
    exit(2);
  } else {
    printf("Connection is good!\n");
  }

  return sock_fd;
}

void send_message(char *msg, int sock_fd) {
  printf("SENDING: %s\n", msg);
  write(sock_fd, msg, strlen(msg));
}

void read_response(char *resp, int sock_fd) {
  int len = read(sock_fd, resp, BUFFER_SIZE-1);
  resp[len] = '\0';

  printf("RECEIVED: %s\n", resp);
}

void RunQuery(char *query) {
  // Connects to the remote server
  int sock_fd = do_connect();

  // Does the query-protocol
  // Gets ACK
  char resp[BUFFER_SIZE];
  read_response(resp, sock_fd);
  if (CheckAck(resp) == -1) {
    printf("Did not receive ACK.\n");
    return;
  }

  // Sends query
  send_message(query, sock_fd);

  // Gets number of responses
  read_response(resp, sock_fd);
  int num_responses = atoi(resp);

  // Sends ACK
  SendAck(sock_fd);

  // For each response 
  for (int i = 0; i < num_responses; i++) {
    // Gets response
    read_response(resp, sock_fd);
    // Sends ACK
    SendAck(sock_fd);
  }

  // Gets GOODBYE
  read_response(resp, sock_fd);
  if (CheckGoodbye(resp) == -1) {
    printf("Did not receive GOODBYE.\n");
    return;
  }

  // Closes the connection
  close(sock_fd); 
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
  // Checks if the input ip is correct 
  if (strcmp(ip, "127.0.0.1") != 0 && strcmp(ip, "localhost") != 0) {
    printf("The ip address was not correct.\n");
    return 0;
  }

  // Connects to the remote server
  int sock_fd = do_connect();

  // Gets ACK
  char resp[1000];
  read_response(resp, sock_fd);
  if (CheckAck(resp) == -1) {
    printf("Did not receive ACK.\n");
    close(sock_fd);
    return 0;
  }

  // Sends GOODBYE
  if (SendGoodbye(sock_fd) == -1) {
    printf("Could not sent GOODBYE.\n");
    close(sock_fd);
    return 0;
  }

  close(sock_fd);
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
