// Student: Emiliano Zhu
// Date: 03/11/2020

// CS 5007, Northeastern University, Seattle
// Summer 2019
// Adrienne Slaughter
//
// Inspired by UW CSE 333; used with permission.
//
// This is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published
//  by the Free Software Foundation, either version 3 of the License,
//  or (at your option) any later version.
// It is distributed in the hope that it will be useful, but
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  General Public License for more details.

#include "LinkedList.h"
#include "LinkedList_priv.h"
#include "Assert007.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList CreateLinkedList() {
  LinkedList list = (LinkedList) malloc(sizeof(LinkedListHead));
  if (list == NULL) {
    // out of memory
    return (LinkedList) NULL;
  }

  list->head = NULL;
  list->tail= NULL;
  list->num_elements = 0U;
  return list;
}

int DestroyLinkedList(LinkedList list,
                      LLPayloadFreeFnPtr payload_free_function) {
  Assert007(list != NULL);
  Assert007(payload_free_function != NULL);

  LinkedListNodePtr destroyed_node = NULL;
  LinkedListNodePtr cur = list->head;
  while (cur != NULL) {
    payload_free_function(cur->payload);
    destroyed_node = cur;
    cur = cur->next;
    DestroyLinkedListNode(destroyed_node);
    }
  list->head = NULL;
  list->tail = NULL;
  list->num_elements = 0U;
  free(list);
  return 0;
}

unsigned int NumElementsInLinkedList(LinkedList list) {
  Assert007(list != NULL);
  return list->num_elements;
}

LinkedListNodePtr CreateLinkedListNode(void *data) {
    LinkedListNodePtr node = (LinkedListNodePtr) malloc(sizeof(LinkedListNode));
    if (node == NULL) {
        // Out of memory
        return NULL;
    }

    node->payload = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

int DestroyLinkedListNode(LinkedListNode *node) {
  Assert007(node != NULL);
  node->payload = NULL;
  node->next = NULL;
  node->prev = NULL;
  free(node);
  return 0;
}

int InsertLinkedList(LinkedList list, void *data) {
  Assert007(list != NULL);
  Assert007(data != NULL);
  LinkedListNodePtr new_node = CreateLinkedListNode(data);

  if (new_node == NULL) {
    return 1;
  }

  if (list->num_elements == 0U) {
    Assert007(list->head == NULL);  // debugging aid
    Assert007(list->tail == NULL);  // debugging aid
    list->head = new_node;
    list->tail = new_node;
    new_node->next = new_node->prev = NULL;
    list->num_elements = 1U;
    return 0;
  }

  LinkedListNodePtr tmp = list->head;
  list->head = new_node;
  list->head->prev = NULL;
  list->head->next = tmp;
  tmp->prev = list->head;
  list->num_elements += 1U;
  return 0;
}

int AppendLinkedList(LinkedList list, void *data) {
  Assert007(list != NULL);
  Assert007(data != NULL);
  LinkedListNodePtr new_node = CreateLinkedListNode(data);

  if (new_node == NULL) {
    return 1;
  }

  if (list->num_elements == 0) {
    Assert007(list->head == NULL);  // debugging aid
    Assert007(list->tail == NULL);  // debugging aid
    list->head = new_node;
    list->tail = new_node;
    new_node->next = new_node->prev = NULL;
    list->num_elements = 1U;
    return 0;
  }

  list->tail->next = new_node;
  new_node->prev = list->tail;
  new_node->next = NULL;
  list->tail = list->tail->next;
  list->num_elements += 1U;
  return 0;
}

int PopLinkedList(LinkedList list, void **data) {
    Assert007(list != NULL);
    Assert007(data != NULL);

    if (list->num_elements == 0) {
      return 0;
    }

    *data = list->head->payload;
    LinkedListNodePtr popped_node = list->head;
    if (list->num_elements == 1U) {
      list->head = NULL;
      list->tail = NULL;
    } else {
      list->head->next->prev = NULL;
      list->head = list->head->next;
    }
    list->num_elements -= 1U;
    DestroyLinkedListNode(popped_node);
    return 0;
}

int SliceLinkedList(LinkedList list, void **data) {
  Assert007(list != NULL);
  Assert007(data != NULL);

  if (list->num_elements == 0) {
    return 0;
  }

  *data = list->tail->payload;
  LinkedListNodePtr sliced_node = list->tail;
  if (list->num_elements == 1U) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list->tail->prev->next = NULL;
    list->tail = list->tail->prev;
  }
  list->num_elements -= 1U;
  DestroyLinkedListNode(sliced_node);
  return 0;
}

void SortLinkedList(LinkedList list,
                    unsigned int ascending,
                    LLPayloadComparatorFnPtr compare) {
    Assert007(list != NULL);
    if (list->num_elements <2) {
        return;
    }

    int swapped;
    do {
      LinkedListNodePtr curnode = list->head;
      swapped = 0;

      while (curnode->next != NULL) {
        // compare this node with the next; swap if needed
        int compare_result = compare(curnode->payload, curnode->next->payload);

        if (ascending) {
          compare_result *= -1;
        }

        if (compare_result < 0) {
          // swap
          void* tmp;
          tmp = curnode->payload;
          curnode->payload = curnode->next->payload;
          curnode->next->payload = tmp;
          swapped = 1;
        }
        curnode = curnode->next;
      }
    } while (swapped);
}

void PrintLinkedList(LinkedList list) {
    printf("List has %lu elements. \n", list->num_elements);
}


LLIter CreateLLIter(LinkedList list) {
  Assert007(list != NULL);
  Assert007(list->num_elements > 0);

  LLIter iter = (LLIter) malloc(sizeof(struct ll_iter));
  Assert007(iter != NULL);

  iter->list = list;
  iter->cur_node = list->head;
  return iter;
}

int LLIterHasNext(LLIter iter) {
  Assert007(iter != NULL);
  return (iter->cur_node->next != NULL);
}

int LLIterNext(LLIter iter) {
  Assert007(iter != NULL);

  if (LLIterHasNext(iter)) {
    iter->cur_node = iter->cur_node->next;
    return 0;
  }
  return 1;
}

int LLIterGetPayload(LLIter iter, void** data) {
  Assert007(iter != NULL);
  *data = iter->cur_node->payload;
  return 0;
}


int LLIterHasPrev(LLIter iter) {
  Assert007(iter != NULL);
  return (iter->cur_node->prev != NULL);
}

int LLIterPrev(LLIter iter) {
  Assert007(iter != NULL);
  if (LLIterHasPrev(iter)) {
    iter->cur_node = iter->cur_node->prev;
    return 0;
  }
  return 1;
}

int DestroyLLIter(LLIter iter) {
  Assert007(iter != NULL);
  iter->cur_node = NULL;
  iter->list = NULL;
  free(iter);
  return 0;
}

int LLIterInsertBefore(LLIter iter, void* payload) {
  Assert007(iter != NULL);
  if ((iter->list->num_elements <= 1) ||
      (iter->cur_node == iter->list->head)) {
    // insert item
    return InsertLinkedList(iter->list, payload);
  }

  LinkedListNodePtr new_node = CreateLinkedListNode(payload);
  if (new_node == NULL) return 1;

  new_node->next = iter->cur_node;
  new_node->prev = iter->cur_node->prev;
  iter->cur_node->prev->next = new_node;
  iter->cur_node->prev = new_node;

  iter->list->num_elements++;

  return 0;
}

int LLIterDelete(LLIter iter, LLPayloadFreeFnPtr payload_free_function) {
  Assert007(iter != NULL);

  if (iter->list->num_elements == 1U) {
    DestroyLinkedList(iter->list, payload_free_function);
    DestroyLLIter(iter);
    return 1;
  }

  LinkedListNodePtr deleted_node = iter->cur_node;
  void* payload;
  if (LLIterHasNext(iter) && !LLIterHasPrev(iter)) {
    LLIterNext(iter);
    PopLinkedList(iter->list, &payload);
    payload_free_function(payload);
  } else if (!LLIterHasNext(iter) && LLIterHasPrev(iter)) {
    LLIterPrev(iter);
    SliceLinkedList(iter->list, &payload);
    payload_free_function(payload);
  } else {
    LLIterNext(iter);
    payload = deleted_node->payload;
    deleted_node->prev->next = deleted_node->next;
    deleted_node->next->prev = deleted_node->prev;
    iter->list->num_elements -= 1;
    DestroyLinkedListNode(deleted_node);
    payload_free_function(payload);
  }
  return 0;
}
