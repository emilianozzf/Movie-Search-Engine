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
  int sflag = 0;
  int cflag = 0;
  int gflag = 0;
  int aflag = 0;
  char* file_name;
  
  int o;
  const char *optstring = "s:c:g:a:";
  if ((o = getopt(argc, argv, optstring)) != -1) {
    switch (o) {
      case 's':
	sflag = 1;
	break;
      case 'c':
	cflag = 1;
        break;
      case 'g':
	gflag = 1;
	break;
      case 'a':
	aflag = 1;
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
  //LinkedList movie_list  = ReadFile(filename);
  //Index index; // STEP 9(Student): Create the index properly. 

  //PrintReport(index);
  //DestroyLinkedList(movie_list, &DestroyNothing);
  //DestroyIndex(index);

  return 0;
}
