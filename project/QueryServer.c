#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
struct addrinfo *result;

#define BUFFER_SIZE 1000

#define SEARCH_RESULT_LENGTH 1500
char movieSearchResult[SEARCH_RESULT_LENGTH];

char* Int2String(int num,char *str) {
    int i = 0;
    if (num < 0) {
       num = -num;
       str[i++] = '-';
    } 
 
    do {
      str[i++] = num % 10 + 48; 
      num /= 10;    
    } while (num);

    str[i] = '\0';

    int j = 0;
    if (str[0]=='-') {
        j = 1; 
        ++i; 
    }
 
    for(; j < i/2; j++) { 
        str[j] = str[j] + str[i-1-j];
        str[i-1-j] = str[j] - str[i-1-j];
        str[j] = str[j] - str[i-1-j];
    } 
    
    return str;
}

void send_message(char *msg, int sock_fd) {
  write(sock_fd, msg, strlen(msg));
 }

void receive_message(char *resp, int sock_fd) {
  int len = read(sock_fd, resp, BUFFER_SIZE - 1);
  resp[len] = '\0';
}

int Cleanup();

void sigint_handler(int sig) {
  write(0, "Exit signal sent. Cleaning up...\n", 34);
  Cleanup();
  exit(0);
}

int HandleClient(int sock_fd) { 
  // Reads, then writes if you want

  // Sends ACK
  SendAck(sock_fd);

  // Listens for query
  char resp[1000];
  receive_message(resp, sock_fd);
  // If query is GOODBYE close ocnnection
  if (CheckGoodbye(resp) == 0) {
    close(sock_fd);
    return 0;
  }

  // Runs query and gets responses
  SearchResultIter results = FindMovies(docIndex, resp);
  if (results == NULL) {
      printf("No results for this term. Please try another.\n");
      return 0;
  }

  // Send number of responses
  int num_responses = NumResultsInIter(results);
  printf("num_responses: %d\n", num_responses);
  write(sock_fd, &num_responses, sizeof(int));

  // Wait for ACK
  receive_message(resp, sock_fd);
  CheckAck(resp);
  
  SearchResult sr = (SearchResult)malloc(sizeof(*sr));
    if (sr == NULL) {
      printf("Couldn't malloc SearchResult in main.c\n");
      return 0;
   }
  int result;
  SearchResultGet(results, sr);
  CopyRowFromFile(sr, docs, movieSearchResult);
  // Sends response
  send_message(movieSearchResult, sock_fd);
  // Waits for ACK 
  receive_message(resp, sock_fd);
  CheckAck(resp);

   while (SearchResultIterHasMore(results) != 0) {
     result = SearchResultNext(results);
     if (result < 0) {
       printf("error retrieving result\n");
       break;
     }
     SearchResultGet(results, sr);
     CopyRowFromFile(sr, docs, movieSearchResult);
     // Sends response
     send_message(movieSearchResult, sock_fd);
     // Waits for ACK
     receive_message(resp, sock_fd);
     CheckAck(resp);
   }
   
   free(sr);
   DestroySearchResultIter(results);
   printf("Destroying search result iter\n");
 
  // Send GOODBYE
  SendGoodbye(sock_fd);

  // close connection.
  close(sock_fd);
  printf("Client connection closes.\n");
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
  freeaddrinfo(result);

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
  // Gets address stuff
  struct addrinfo hints;

  // Sets up the hints struct
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  s = getaddrinfo(NULL, port, &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(1);
  }

  // Opens the socket
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  
  // Binds the socket
  if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
    perror("bind()");
    exit(1);
  }

  // Listens on the socket
  if (listen(sock_fd, 10) != 0) {
    perror("listen()");
    exit(1);
  }

  struct sockaddr_in *result_addr = (struct sockaddr_in *) result->ai_addr;
  printf("Listening on file descriptor %d, port %d\n", sock_fd, ntohs(result_addr->sin_port));

  while (1) {
    // Accepts a connection
    printf("Waiting for connection...\n");
    int client_fd = accept(sock_fd, NULL, NULL);
    printf("Client connected\n");
 
    HandleClient(client_fd);
  }

  // Got Kill signal
  close(sock_fd);
  freeaddrinfo(result);
  Cleanup();

  return 0;
}
