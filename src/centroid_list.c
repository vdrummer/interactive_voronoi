#include <stdlib.h>

#include "centroid_list.h"

typedef struct centroid_list_node CentroidListNode;
struct centroid_list_node {
  Centroid point;
  CentroidListNode* next;
};

struct centroid_list {
  size_t size;
  CentroidListNode* current;
  CentroidListNode* head;
  CentroidListNode* tail;
};

CentroidList* centroid_list_init() {
  CentroidList* pl = malloc(sizeof(CentroidList));
  if (pl == NULL) {
    return NULL;
  }

  pl->size = 0;
  pl->current = NULL;
  pl->head = NULL;
  pl->tail = NULL;

  return pl;
}

void centroid_list_free(CentroidList* pl) {
  if (pl == NULL) {
    return;
  }

  CentroidListNode* current = pl->head;

  while (current != NULL) {
    CentroidListNode* next = NULL;
    if (current->next) {
      next = current->next;
    }

    free(current);
    current = next;
  }

  free(pl);
}

void centroid_list_append(CentroidList* pl, Centroid p) {
  if (pl == NULL) {
    return;
  }

  CentroidListNode* node = malloc(sizeof(CentroidListNode));
  if (node == NULL) {
    return;
  }

  node->point = p;
  node->next = NULL;

  if (pl->tail == NULL) {
    pl->head = node;
    pl->tail = node;
    pl->current = node;
  } else {
    pl->tail->next = node;
    pl->tail = node;
  }

  pl->size++;
}

void centroid_list_remove(CentroidList* pl, size_t index) {
  if (pl == NULL) {
    return;
  }

  if (index >= pl->size) {
    return;
  }

  if (index == 0) {
    CentroidListNode* tmp = pl->head;
    pl->head = pl->head->next;

    if (pl->head == NULL) {
      pl->tail = NULL;
      pl->current = NULL;
    }

    if (pl->current == tmp) {
      pl->current = pl->head;
    }

    free(tmp);
  } else {
    CentroidListNode* current = pl->head;
    size_t count = 0;

    while (current != NULL && count < index - 1) {
      current = current->next;
      count++;
    }

    // current is now at target.previous
    if (current->next == NULL) {
      return;
    }

    CentroidListNode* tmp = current->next;
    current->next = current->next->next;

    if (pl->tail == tmp) {
      pl->tail = current;
    }

    if (pl->current == tmp) {
      pl->current = current->next;
    }

    free(tmp);
  }

  pl->size--;
}

Centroid* centroid_list_getNext(CentroidList* pl) {
  if (pl == NULL) {
    return NULL;
  }

  Centroid* p = &pl->current->point;
  if (pl->current != NULL) {
    pl->current = pl->current->next;
  }

  return p;
}

void centroid_list_resetIterator(CentroidList* pl) {
  if (pl == NULL) {
    return;
  }

  pl->current = pl->head;
}

size_t centroid_list_getSize(CentroidList* cl) {
  if (cl == NULL) {
    return 0;
  }

  return cl->size;
}
