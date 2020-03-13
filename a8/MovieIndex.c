/*
 *  Adrienne Slaughter
 *  5007 Spr 2020
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
#include <string.h>
#include <ctype.h>

#include "MovieIndex.h"
#include "htll/LinkedList.h"
#include "htll/Hashtable.h"
#include "Movie.h"
#include "MovieSet.h"

void DestroyMovieSetWrapper(void *movie_set) {
  DestroyMovieSet((MovieSet)movie_set);
}

void toLower(char *str, int len) {
  for (int i = 0; i < len; i++) {
    str[i] = tolower(str[i]);
  }
}

Index BuildMovieIndex(LinkedList movies, enum IndexField field_to_index) {
  // TODO(Student): This 100 is a magic number. 
  // Is there a better way to initialize this? If so, do it. 
  Index movie_index = CreateHashtable(100);

  LLIter iter = CreateLLIter(movies);
  Movie* cur_movie;
  LLIterGetPayload(iter, (void**)&cur_movie);

  // TODO: Check that there is at least one movie
  // What happens if there is not at least one movie?
  int result = AddMovieToIndex(movie_index, cur_movie, field_to_index);

  while (LLIterHasNext(iter)) {
    LLIterNext(iter);
    LLIterGetPayload(iter, (void**)&cur_movie);
    result = AddMovieToIndex(movie_index, cur_movie, field_to_index);
  }
  DestroyLLIter(iter);
  return movie_index;
}


int AddMovieActorsToIndex(Index index, Movie *movie) {
  HTKeyValue kvp;
  HTKeyValue old_kvp;

  // TODO(Student): Add movies to the index via actors. 

  AddMovieToSet((MovieSet)kvp.value, movie);
}

int AddMovieToIndex(Index index, Movie *movie, enum IndexField field) {
  if (field == Actor) {
    return AddMovieActorsToIndex(index, movie);
  }

  // TODO(Student): How do we add movies to the index? 

  AddMovieToSet((MovieSet)kvp.value, movie);

  return 0;
}

uint64_t ComputeKey(Movie* movie, enum IndexField which_field) {
  char rating_str[10];
  switch (which_field) {
    case Genre:
      return FNVHash64((unsigned char*)movie->genre, strlen(movie->genre));
    case StarRating:
      snprintf(rating_str, 10, "%f", movie->star_rating);
      return FNVHash64((unsigned char*)rating_str, strlen(rating_str));
    case ContentRating:
      return FNVHash64((unsigned char*)movie->content_rating,
                       strlen(movie->content_rating));
    case Actor:
      break;
  }
  return -1u;
}

MovieSet GetMovieSet(Index index, const char *term) {
  HTKeyValue kvp;
  char lower[strlen(term)+1];
  snprintf(lower, strlen(term) + 1, "%s", term);
  toLower(lower, strlen(lower));
  int result = LookupInHashtable(index, FNVHash64((unsigned char*)lower,
                                                  (unsigned int)strlen(lower)), &kvp);
  if (result < 0) {
    printf("term couldn't be found: %s \n", term);
    return NULL;
  }
  return (MovieSet)kvp.value;
}

int DestroyIndex(Index index) {
  DestroyHashtable(index, &DestroyMovieSetWrapper);
  return 0;
}

Index CreateIndex() {
  return CreateHashtable(128);
}
