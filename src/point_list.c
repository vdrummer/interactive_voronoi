#include <stdlib.h>

#include "point_list.h"

typedef struct point_list_node PointListNode;
struct point_list_node {
  Point point;
  PointListNode* next;
};

struct point_list {
  size_t size;
  PointListNode* current;
  PointListNode* head;
  PointListNode* tail;
};

PointList* point_list_init() {
  PointList* pl = malloc(sizeof(PointList));
  if (pl == NULL) {
    return NULL;
  }

  pl->size = 0;
  pl->current = NULL;
  pl->head = NULL;
  pl->tail = NULL;

  return pl;
}

void point_list_free(PointList* pl) {
  if (pl == NULL) {
    return;
  }

  PointListNode* current = pl->head;

  while (current != NULL) {
    PointListNode* next = NULL;
    if (current->next) {
      next = current->next;
    }

    free(current);
    current = next;
  }

  free(pl);
}

void point_list_append(PointList* pl, Point p) {
  if (pl == NULL) {
    return;
  }

  PointListNode* node = malloc(sizeof(PointListNode));
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
  }

  pl->size++;
}

void point_list_remove(PointList* pl, size_t index) {
  if (pl == NULL) {
    return;
  }

  if (index >= pl->size) {
    return;
  }

  if (index == 0) {
    PointListNode* tmp = pl->head;
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
    PointListNode* current = pl->head;
    size_t count = 0;

    while (current != NULL && count < index - 1) {
      current = current->next;
      count++;
    }

    // current is now at target.previous
    //TODO remove node
    if (current->next == NULL) {
      return;
    }

    PointListNode* tmp = current->next;
    current->next = current->next->next;

    if (pl->tail == tmp) {
      pl->tail = current;
    }

    if (pl->current == tmp) {
      pl->current = current->next;
    }

    free(tmp);
  }
}

Point* point_list_getNext(PointList* pl) {
  if (pl == NULL) {
    return NULL;
  }

  Point* p = &pl->current->point;
  if (pl->current != NULL) {
    pl->current = pl->current->next;
  }

  return p;
}

void point_list_resetIterator(PointList* pl) {
  if (pl == NULL) {
    return;
  }

  pl->current = pl->head;
}
