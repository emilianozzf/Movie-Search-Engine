/*
 *  Name: Emiliano Zhu                                                                                             
 *  Date: 2020/04/01
 * 
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "QueryProcessor.h"
#include "MovieTitleIndex.h"
#include "LinkedList.h"
#include "Hashtable.h"
#include "DocSet.h"

SearchResultIter CreateSearchResultIter(DocumentSet set) {
  SearchResultIter iter =
    (SearchResultIter) malloc(sizeof(struct searchResultIter));

  if (iter == NULL) {
    printf("cannot allocate memory for search restult iterator\n");
    return NULL;
  }
  iter->doc_iter = CreateHashtableIterator(set->doc_index);

  HTKeyValue dest;
  HTIteratorGet(iter->doc_iter, &dest);
  iter->cur_doc_id = dest.key;
  iter->offset_iter = CreateLLIter(dest.value);
  return iter;
}

void DestroySearchResultIter(SearchResultIter iter) {
  if (iter->offset_iter != NULL) {
    DestroyLLIter(iter->offset_iter);
  }
  DestroyHashtableIterator(iter->doc_iter);
  free(iter);
}

SearchResultIter FindMovies(MovieTitleIndex index, char *term) {
  DocumentSet set = GetDocumentSet(index, term);
  if (set == NULL) {
    return NULL;
  }
  printf("Getting docs for movieset term: \"%s\"\n", set->desc);
  SearchResultIter iter = CreateSearchResultIter(set);
  return iter;
}


int SearchResultGet(SearchResultIter iter, SearchResult output) {
  output->doc_id = iter->cur_doc_id;
  int* payload;
  LLIterGetPayload(iter->offset_iter, (void**) &payload);
  output->row_id = *payload;
  return 0;
}

int SearchResultNext(SearchResultIter iter) {
  int res = LLIterNext(iter->offset_iter);
  if (res == 0) {
    return 0;
  }

  res = HTIteratorNext(iter->doc_iter);
  if (res == 0) {
    DestroyLLIter(iter->offset_iter);
    HTKeyValue dest;
    res = HTIteratorGet(iter->doc_iter, &dest);
    iter->cur_doc_id = dest.key;
    iter->offset_iter = CreateLLIter(dest.value);
    return 0;
  }

  return -1;
}

int SearchResultIterHasMore(SearchResultIter iter) {
  if (iter->doc_iter == NULL) {
    return 0;
  }
  if (LLIterHasNext(iter->offset_iter) == 0) {
    return (HTIteratorHasMore(iter->doc_iter));
  }
  return 1;
}
