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
  Index movie_index = CreateIndex();

  if (NumElementsInLinkedList(movies) == 0) {
    return movie_index;
  }
  
  LLIter iter = CreateLLIter(movies);
  Movie* cur_movie;
  LLIterGetPayload(iter, &cur_movie);

  int result = AddMovieToIndex(movie_index, cur_movie, field_to_index);
  
  while (LLIterHasNext(iter) == 1) {
    LLIterNext(iter);
    LLIterGetPayload(iter, &cur_movie);
    result = AddMovieToIndex(movie_index, cur_movie, field_to_index);
  }
  DestroyLLIter(iter);
  return movie_index;
}

int ContainsMovie(MovieSet movie_set, Movie* movie) {
  if (NumElementsInLinkedList(movie_set->movies) == 0) {
    return 0;
  }
  
  LLIter iter = CreateLLIter(movie_set->movies);
  Movie* item;
  LLIterGetPayload(iter, &item);
  
  if (item == movie) {
    DestroyLLIter(iter);
    return 1;
  }

  while (LLIterHasNext(iter) == 1) {
    LLIterNext(iter);
    LLIterGetPayload(iter, &item);
    if	(item == movie) {
      DestroyLLIter(iter);
      return 1;
    }
  }

  DestroyLLIter(iter);
  return 0;
}


int AddMovieActorsToIndex(Index index, Movie *movie) {
  HTKeyValue kvp;
  HTKeyValue old_kvp;

  for (int i = 0; i < movie->num_actors; i++) {
    kvp.key = ComputeKey(movie, Actor, i);
    int res = LookupInHashtable(index, kvp.key, &kvp);
    
    if (res == -1) {
      kvp.value = CreateMovieSet(movie->actor_list[i]);
      PutInHashtable(index, kvp, &old_kvp);
    }
    
    if (ContainsMovie(kvp.value, movie) == 1) {
       continue;
    }
    
    AddMovieToSet((MovieSet)kvp.value, movie);
  }
  return 0;
}

int AddMovieToIndex(Index index, Movie *movie, enum IndexField field) {
  if (field == Actor) {
    return AddMovieActorsToIndex(index, movie);
  }

  HTKeyValue kvp;
  HTKeyValue old_kvp;
  kvp.key = ComputeKey(movie, field, 0);
  int res = LookupInHashtable(index, kvp.key, &kvp);
  
  if (res == -1) {
    char rating_str[10];
    MovieSet new_movie_set;
    
    switch (field) {
      case Genre:
	new_movie_set = CreateMovieSet(movie->genre);
	break;
      case StarRating:
        snprintf(rating_str, 10, "%f", movie->star_rating);
        new_movie_set = CreateMovieSet(rating_str);
	break;
      case ContentRating:
        new_movie_set = CreateMovieSet(movie->content_rating);
	break;
    }
    kvp.value = new_movie_set;
    int result = PutInHashtable(index, kvp, &old_kvp);
  }

  if (ContainsMovie(kvp.value, movie) == 1) {
    return -1;
  }

  AddMovieToSet((MovieSet)kvp.value, movie);
  return 0;
}


uint64_t ComputeKey(Movie* movie, enum IndexField which_field, int which_actor) {
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
      if (which_actor < movie->num_actors) {
        return FNVHash64((unsigned char*)movie->actor_list[which_actor],
                         strlen(movie->actor_list[which_actor]));
      }
      break;
  }
  return -1u;
}

// Removed for simplicity
//MovieSet GetMovieSet(Index index, const char *term){}

int DestroyIndex(Index index) {
  DestroyHashtable(index, &DestroyMovieSetWrapper);
  return 0;
}

Index CreateIndex() {
  return CreateHashtable(128);
}
