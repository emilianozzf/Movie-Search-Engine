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

#ifndef _FILEPARSER_H
#define _FILEPARSER_H

#include "htll/LinkedList.h"
#include "Movie.h"
#include "MovieIndex.h"



/**
 * Reads in the specified file with a given structure and reads in each row,
 * creating a Movie from each row.
 *
 * Expected sample row:
 * id       |type |Title1   |Title2   |IsAdult|Year|?|?|Genres
 * tt0003609|movie|Alexandra|Alexandra|0      |1915|-|-|-
 *
 * Fields are separated by a pipe (|), and a dash (-) specifies an empty value.
 *
 * INPUT: filename: the data file with movies
 *
 * Returns a LinkedList of Movie structs from the specified file
 */

LinkedList ReadFile(char* filename);

/**
 * Given a char* that is a row in the data file,
 * Creates and populates a Movie struct accordingly.
 * Expected sample row:
 * id       |type |Title1   |Title2   |IsAdult|Year|?|?|Genre
 * tt0003609|movie|Alexandra|Alexandra|0      |1915|-|-|-
 *
 * Fields are separated by a pipe (|), and a dash (-) specifies an empty value.
 *
 * Returns: A pointer to a Movie struct that has been allocated and populated.
 */

Movie* CreateMovieFromRow(char *dataRow);

#endif  // _FILEPARSER_H
