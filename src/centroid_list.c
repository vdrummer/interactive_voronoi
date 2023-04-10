#include <stdlib.h>

#include "centroid_list.h"

typedef struct centroid_list_node CentroidListNode;
struct centroid_list_node {
  Centroid centroid;
  CentroidListNode* next;
};

struct centroid_list {
  size_t size;
  CentroidListNode* current;
  CentroidListNode* head;
  CentroidListNode* tail;
};

CentroidList* centroid_list_init() {
  CentroidList* cl = malloc(sizeof(CentroidList));
  if (cl == NULL) {
    return NULL;
  }

  cl->size = 0;
  cl->current = NULL;
  cl->head = NULL;
  cl->tail = NULL;

  return cl;
}

void centroid_list_free(CentroidList* cl) {
  if (cl == NULL) {
    return;
  }

  CentroidListNode* current = cl->head;

  while (current != NULL) {
    CentroidListNode* next = NULL;
    if (current->next) {
      next = current->next;
    }

    free(current);
    current = next;
  }

  free(cl);
}

void centroid_list_append(CentroidList* cl, Centroid c) {
  if (cl == NULL) {
    return;
  }

  CentroidListNode* node = malloc(sizeof(CentroidListNode));
  if (node == NULL) {
    return;
  }

  node->centroid = c;
  node->next = NULL;

  if (cl->tail == NULL) {
    cl->head = node;
    cl->tail = node;
    cl->current = node;
  } else {
    cl->tail->next = node;
    cl->tail = node;
  }

  cl->size++;
}

void centroid_list_remove(CentroidList* cl, size_t index) {
  if (cl == NULL) {
    return;
  }

  if (index >= cl->size) {
    return;
  }

  if (index == 0) {
    CentroidListNode* tmp = cl->head;
    cl->head = cl->head->next;

    if (cl->head == NULL) {
      cl->tail = NULL;
      cl->current = NULL;
    }

    if (cl->current == tmp) {
      cl->current = cl->head;
    }

    free(tmp);
  } else {
    CentroidListNode* current = cl->head;
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

    if (cl->tail == tmp) {
      cl->tail = current;
    }

    if (cl->current == tmp) {
      cl->current = current->next;
    }

    free(tmp);
  }

  cl->size--;
}

Centroid* centroid_list_getNext(CentroidList* cl) {
  if (cl == NULL) {
    return NULL;
  }

  Centroid* c = &cl->current->centroid;
  if (cl->current != NULL) {
    cl->current = cl->current->next;
  }

  return c;
}

void centroid_list_resetIterator(CentroidList* cl) {
  if (cl == NULL) {
    return;
  }

  cl->current = cl->head;
}

size_t centroid_list_getSize(CentroidList* cl) {
  if (cl == NULL) {
    return 0;
  }

  return cl->size;
}

void centroid_list_setIterator(CentroidList* cl, size_t index) {
  if (cl == NULL) {
    return;
  }

  if (index >= cl->size) {
    return;
  }

  CentroidListNode* node = cl->head;
  size_t counter = 0;

  while (counter < index && node != NULL) {
    counter++;
    node = node->next;
  }

  cl->current = node;
}

void centroid_list_removeClosest(CentroidList* cl, Point p) {
  if (cl == NULL) {
    return;
  }

  CentroidListNode* current = cl->head;
  if (current == NULL) {
    return;
  }

  size_t closestIndex = 0;
  int closestDistance = point_fakeDist(current->centroid.point, p);

  size_t index = 1;
  current = current->next;

  while (current != NULL) {
    int dist = point_fakeDist(current->centroid.point, p);

    if (dist < closestDistance) {
      closestDistance = dist;
      closestIndex = index;
    }

    current = current->next;
    index++;
  }
  
  centroid_list_remove(cl, closestIndex);
}
