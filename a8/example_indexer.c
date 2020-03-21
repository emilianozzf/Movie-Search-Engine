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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <ctype.h>
#include <unistd.h>


#include "htll/LinkedList.h"
#include "MovieIndex.h"
#include "Movie.h"
#include "MovieReport.h"
#include "./FileParser.h"

void DestroyNothing(void* thing) {
  // Helper method to destroy the LinkedList.
}

int main(int argc, char* argv[]) {
  enum IndexField field_to_index;
  
  int o;
  const char *optstring = "s:c:g:a:";
  if ((o = getopt(argc, argv, optstring)) != -1) {
    switch (o) {
      case 's':
	field_to_index = StarRating;
	break;
      case 'c':
	field_to_index = ContentRating;
        break;
      case 'g':
	field_to_index = Genre;
	break;
      case 'a':
	field_to_index = Actor;
	break;
      case '?':
	printf("error optopt: %c\n", optopt);
	printf("error opterr: %d\n", opterr);
	break;
    }
  } else {
    printf("usage: ./example -s/-c/-g/-a data/test (one and only one flag may be provided)\n");
  }
  
  char* filename = optarg;
  LinkedList movie_list  = ReadFile(filename);
  Index index =  BuildMovieIndex(movie_list, field_to_index);

  //PrintReport(index);
  DestroyLinkedList(movie_list, &DestroyNothing);
  DestroyIndex(index);

  return 0;
}
