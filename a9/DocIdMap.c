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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DocIdMap.h"
#include "Hashtable.h"

void DestroyString(void *val) {
    free(val);
}

DocIdMap CreateDocIdMap() {
  DocIdMap docs = (DocIdMap)CreateHashtable(64);
  return docs;
}

void DestroyDocIdMap(DocIdMap map) {
  DestroyHashtable(map, &DestroyString);
}

int PutFileInMap(char *filename, DocIdMap map) {
  HTKeyValue kvp;
  HTKeyValue old_kvp;
  kvp.key = (uint64_t) (NumElemsInHashtable(map) + 1);
  kvp.value = filename;
  int res = PutInHashtable(map, kvp, &old_kvp);
  while (res == 2) {
    if (strcmp(filename, (char*)old_kvp.value) != 0) {
      kvp.key += 1;
      res = PutInHashtable(map, kvp, &old_kvp);
    } else {
      return 0;
    }
  }
  return 0;
}

DocIdIter CreateDocIdIterator(DocIdMap map) {
  DocIdIter iter = (DocIdIter)CreateHashtableIterator(map);
  return iter;
}

void DestroyDocIdIterator(DocIdIter iter) {
  DestroyHashtableIterator(iter);
}

char *GetFileFromId(DocIdMap docs, int docId) {
  HTKeyValue result;
  int res = LookupInHashtable(docs, (uint64_t)docId, &result);
  if (res == 0) {
    return (char*)result.value;
  }
  return NULL;
}
