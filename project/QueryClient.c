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

  // Create the socket

  // Connect to the server

  // Do the query-protocol

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
  // Listen for an ACK
  // Send a goodbye
  // Close the connection
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Incorrect number of arguments. \n");
    printf("Correct usage: ./queryclient [IP] [port]\n");
  } else {
    ip = argv[1];
    port_string = argv[2];
  }

  if (CheckIpAddress(ip, port_string)) {
    RunPrompt();
  }
  return 0;
}
