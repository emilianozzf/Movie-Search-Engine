#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#include "DirectoryParser_MT.h"
#include "QueryProtocol.h"
#include "MovieSet.h"
#include "MovieIndex.h"
#include "MovieTitleIndex.h"
#include "DocIdMap.h"
#include "Hashtable.h"
#include "QueryProcessor.h"
#include "FileParser.h"
#include "FileCrawler.h"
#include "DirectoryParser.h"
#include "Util.h"

DocIdMap docs;
MovieTitleIndex docIndex;

#define BUFFER_SIZE 1000

#define SEARCH_RESULT_LENGTH 1500
char movieSearchResult[SEARCH_RESULT_LENGTH];

void send_message(char *msg, int sock_fd) {
  printf("SENDING: %s\n", msg);
  write(sock_fd, msg, strlen(msg));
 }

void receive_message(char *resp, int sock_fd) {
  int len = read(sock_fd, resp, 999);
  resp[len] = '\0';

  printf("RECEIVED: %s\n", resp);
}

int Cleanup();

void sigint_handler(int sig) {
  write(0, "Exit signal sent. Cleaning up...\n", 34);
    Cleanup();
  exit(0);
}

int HandleClient(int sock_fd) {
  
  // Step 6: Read, then write if you want

  // Send ACK
  SendAck(sock_fd);

  // Listen for query
  char resp[1000];
  receive_message(resp, sock_fd);
  // If query is GOODBYE close ocnnection
  if (CheckGoodbye(resp) == 0) {
    close(sock_fd);
    return 0;
  }

  // Run query and get responses
  printf("Run query and get responses!\n");
  
  // Send number of responses
  send_message("number of responses", sock_fd);
  
  // Wait for ACK
  receive_message(resp, sock_fd);

  // For each response
  
    // Send response
  send_message("response!", sock_fd);
    // Wait for ACK
  receive_message(resp, sock_fd);
 
  // Cleanup

  // Send GOODBYE
  SendGoodbye(sock_fd);

  // close connection.
  close(sock_fd);
  return 0;
}

int Setup(char *dir) {
  printf("Crawling directory tree starting at: %s\n", dir);
  // Create a DocIdMap
  docs = CreateDocIdMap();
  CrawlFilesToMap(dir, docs);
  printf("Crawled %d files.\n", NumElemsInHashtable(docs));

  // Create the index
  docIndex = CreateMovieTitleIndex();

  if (NumDocsInMap(docs) < 1) {
    printf("No documents found.\n");
    return 0;
  }

  // Index the files
  printf("Parsing and indexing files...\n");
  ParseTheFiles(docs, docIndex);
  printf("%d entries in the index.\n", NumElemsInHashtable(docIndex->ht));
  return NumElemsInHashtable(docIndex->ht);
}

int Cleanup() {
  DestroyMovieTitleIndex(docIndex);
  DestroyDocIdMap(docs);

  return 0;
}

int main(int argc, char **argv) {
  char *port = NULL;
  char *dir_to_crawl = NULL;

  int debug_flag = 0;
  int c;

  while ((c = getopt (argc, argv, "dp:f:")) != -1) {
    switch (c)
      {
      case 'd':
        debug_flag = 1;
        break;
      case 'p':
        port = optarg;
        break;
      case 'f':
        dir_to_crawl = optarg;
        break;
      }
  }

  if (port == NULL) {
    printf("No port provided; please include with a -p flag.\n");
    exit(0);
  }

  if (dir_to_crawl == NULL) {
    printf("No directory provided; please include with a -f flag.\n");
    exit(0);
  }

  // Setup graceful exit
  struct sigaction kill;

  kill.sa_handler = sigint_handler;
  kill.sa_flags = 0;  // or SA_RESTART
  sigemptyset(&kill.sa_mask);

  if (sigaction(SIGINT, &kill, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  int num_entries = Setup(dir_to_crawl);
  if (num_entries == 0) {
    printf("No entries in index. Quitting. \n");
    exit(0);
  }

  int s;
  // Step 1: Get address stuff
  struct addrinfo hints, *result;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  s = getaddrinfo(NULL, port, &hints, &result);
  if (s != 0) {
    printf("Could not get the address.\n");
    exit(1);
  }

  // Step 2: Open socket
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  
  // Step 3: Bind socket
  if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
    perror("bind()");
    exit(1);
  }
  
  // Step 4: Listen on the socket
  if (listen(sock_fd, 10) != 0) {
    perror("listen()");
    exit(1);
  }

  struct sockaddr_in *result_addr = (struct sockaddr_in *) result->ai_addr;
  printf("Listening on file descriptor %d, port %d\n", sock_fd, ntohs(result_addr->sin_port));

  while (1) {
    // Step 5: Accepts a connection
    printf("Waiting for connection...\n");
    int client_fd = accept(sock_fd, NULL, NULL);
    printf("Conncetion made: client_fd=%d\n", client_fd);
    
    HandleClient(client_fd);
  }
  // Got Kill signal
  // close(sock_fd);

  Cleanup();

  return 0;
}
