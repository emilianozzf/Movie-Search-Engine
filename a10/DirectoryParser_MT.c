/*
 *  Created by Adrienne Slaughter
 *  CS 5007 Summer 2019
 *  Northeastern University, Seattle
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  See <http://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

#include "DirectoryParser.h"
#include "MovieTitleIndex.h"
#include "Movie.h"
#include "DocIdMap.h"


#define BUFFER_SIZE 1000

//=======================
// To minimize the number of files we have, I'm
// putting the private function prototypes for
// the DirectoryParser here.

/**
 * Helper function to index a single file. 
 *
 * \return a pointer to the number of records (lines) indexed from the file
 */
void* IndexAFile_MT(void *toBeIter);

pthread_mutex_t ITER_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t INDEX_MUTEX = PTHREAD_MUTEX_INITIALIZER;

MovieTitleIndex movieIndex;

int ParseTheFiles_MT(DocIdMap docs, MovieTitleIndex index, int num_threads) {
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  DocIdIter iter = CreateDocIdIterator(docs);
  movieIndex = index;
  pthread_t[] tids = pthread_t[num_threads];
  int*[] num_records = int*[num_threads];
  int res = 0;

  
  for (int i = 0; i < num_threads; i++) {
    if (HTIteratorHasMore(iter) != 0) {
      pthread_create(&tids[i], NULL, IndexAFile_MT, iter);
      pthread_join(tids[i], num_records[i]);
      HTIteratorNext(iter);
      res += *num_records[i];
      free(num_records[i]);
    }
  }
  
  pthread_mutex_destroy(&ITER_MUTEX);
  pthread_mutex_destroy(&INDEX_MUTEX);

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  printf("Took %f seconds to execute. \n", cpu_time_used);
  return 0;
}

void* IndexAFile_MT(void *docname_iter) {
  pthread_mutex_lock(&ITER_MUTEX);
  HTIter iter = (HTIter) docname_iter;
  HTKeyValue dest;
  HTIteratorGet(iter, &dest);
  uint64_t doc_id = dest.key;
  char* file = (char*) dest.value;
  pthread_mutex_unlock(&ITER_MUTEX);

  FILE *cfPtr;
  if ((cfPtr = fopen(file, "r")) == NULL) {
    printf("File could not be opened\n");
    return 0;
  } else {
    char buffer[kBufferSize];
    int* num_records = (int*) malloc(sizeof(int));
    *num_records = 0;
    
    while (fgets(buffer, kBufferSize, cfPtr) != NULL) {
      Movie* movie = CreateMovieFromRow(buffer);
      pthread_mutex_lock(&INDEX_MUTEX);
      int result = AddMovieTitleToIndex(movieIndex, movie, doc_id, row);
      pthread_mutex_unlock(&INDEX_MUTEX);
      if (result < 0) {
        fprintf(stderr, "Didn't add MovieToIndex.\n");
      }
      *num_records++;
      DestroyMovie(movie);
    }
    fclose(cfPtr);
    return (void*)num_records;
  }
}
