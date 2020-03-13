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
#include <stdint.h>
#include <assert.h>

#include "gtest/gtest.h"

extern "C" {
  #include "./FileParser.h"
  #include "htll/LinkedList.h"
  #include "MovieIndex.h"
  #include "Movie.h"
}

const char* movie_row_A = "9.3|The Shawshank Redemption|R|Crime|142|[u'Tim Robbins', u'Morgan Freeman', u'Bob Gunton']";
const char* movie_row_B = "7.4|Back to the Future Part III|PG|Adventure|118|'Michael J. Fox' 'Christopher Lloyd' 'Mary Steenburgen'";

void DestroyLLMovie(void *payload) {
  DestroyMovie((Movie*)payload);
}

TEST(FileParser, ReadGoodFile) {
  // read a file
  LinkedList movie_list  = ReadFile(const_cast<char *>("data/test"));

  ASSERT_EQ(5u, NumElementsInLinkedList(movie_list));

  DestroyLinkedList(movie_list, &DestroyLLMovie);
}


TEST(Movie, CreateFromRow) {
  // Copying the string from a const to an array
  // (to be more similar to the actual use case)
  char row[1000];
  strcpy(row, movie_row_A);
  // Create from a "good" row


  Movie* m1 = CreateMovieFromRow(row);
  ASSERT_EQ(9.3, m1->star_rating);
  ASSERT_EQ(0, strcmp(m1->content_rating, "R"));
  ASSERT_EQ(0, strcmp(m1->title, "The Shawshank Redemption"));
  ASSERT_EQ(142, m1->duration);
  ASSERT_EQ(0, strcmp(m1->genre, "Crime"));
  //  ASSERT_EQ(-1, m1->actor_list); // TODO: Check actors
            
  
  // TODO: Create from a improper row

  DestroyMovie(m1); 
  
}

TEST(FileParser, ReadNonexistentFile) {
  // try to read a non-existent file
  LinkedList movie_list = ReadFile(const_cast<char *>("bogus/file"));
  ASSERT_TRUE(movie_list == NULL);

}


TEST(FileParser, ReadBinaryFile) {
  // try to read a file that contains non-ASCII text
  LinkedList movie_list;

  movie_list = ReadFile(const_cast<char *>("./movies_small/libhtll.a"));
  ASSERT_TRUE(movie_list == NULL);
}

TEST(FileParser, BuildMovieIndex) {
  LinkedList movie_list  = ReadFile(const_cast<char *>("data/test"));

  ASSERT_EQ(5u, NumElementsInLinkedList(movie_list));

  Index index = BuildMovieIndex(movie_list, Genre);

  // Do a few spot checks.
  DestroyIndex(index);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
