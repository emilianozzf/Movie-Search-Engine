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
#include <string.h>

#include "DocSet.h"
#include "Hashtable.h"
#include "Util.h"

int ContainsCertainRow(LinkedList row_ids, int rowId) {
  if (NumElementsInLinkedList(row_ids) == 0) {
    return 0;
  }
  
  LLIter iter = CreateLLIter(row_ids);
  int* payload;
  LLIterGetPayload(iter, (void**)&payload);
  if (&payload == rowId) {
    return 1;
    DestroyLLIter(iter);
  }
  while (LLIterHasNext(iter) == 1) {
    LLIterNext(iter);
    LLIterGetPayload(iter, (void**)&payload);
    if	(&payload == rowId) {
      return 1;
      DestroyLLIter(iter);
    }
  }
  DestroyLLIter(iter);
  return 0;
}

int AddDocInfoToSet(DocumentSet set,  uint64_t docId, int rowId) {
  HTKeyValue kvp;
  HTKeyValue old_kvp;
  kvp.key = docId;
  int res = LookupInHashtable(set->doc_index, kvp.key, &kvp);
  
  if (res == -1) {
    LinkedList row_ids = CreateLinkedList();
    kvp.value = (void*)row_ids;
    PutInHashtable(set->doc_index, kvp, &old_kvp);
  }

  int* row_id_ptr = (int*)malloc(sizeof(int));
  *row_id_ptr = rowId;
  if (ContainsCertainRow((LinkedList)kvp.value, rowId) == 0) {
    InsertLinkedList((LinkedList)kvp.value, row_id_ptr);
    return 0;
  }
  return -1;
}

int DocumentSetContainsDoc(DocumentSet set, uint64_t docId) {
  // STEP 5: Implement DocumentSetContainsDoc
  return -1;
}

void PrintOffsetList(LinkedList list) {
  printf("Printing offset list\n");
  LLIter iter = CreateLLIter(list);
  int* payload;
  while (LLIterHasNext(iter) != 0) {
    LLIterGetPayload(iter, (void**)&payload);
    printf("%d\t", *((int*)payload));
    LLIterNext(iter);
  }
}


DocumentSet CreateDocumentSet(char *desc) {
  DocumentSet set = (DocumentSet)malloc(sizeof(struct docSet));
  if (set == NULL) {
    // Out of memory
    printf("Couldn't malloc for movieSet %s\n", desc);
    return NULL;
  }
  int len = strlen(desc);
  set->desc = (char*)malloc((len + 1) *  sizeof(char));
  if (set->desc == NULL) {
    printf("Couldn't malloc for movieSet->desc");
    return NULL;
  }
  snprintf(set->desc, len + 1, "%s", desc);
  set->doc_index = CreateHashtable(16);
  return set;
}

void DestroyOffsetList(void *val) {
  LinkedList list = (LinkedList)val;
  DestroyLinkedList(list, &SimpleFree);
}

void DestroyDocumentSet(DocumentSet set) {
  // Free desc
  free(set->desc);
  // Free doc_index
  DestroyHashtable(set->doc_index, &DestroyOffsetList);
  // Free set
  free(set);
}