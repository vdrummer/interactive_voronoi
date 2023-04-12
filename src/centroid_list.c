#include <stdlib.h>
#include <stdio.h>

#include "centroid_list.h"

typedef struct centroid_list_node CentroidListNode;
struct centroid_list_node {
  Centroid centroid;
  CentroidListNode* next;
};

struct centroid_list {
  int size;
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

void centroid_list_remove(CentroidList* cl, int index) {
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
    int count = 0;

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

int centroid_list_getSize(CentroidList* cl) {
  if (cl == NULL) {
    return 0;
  }

  return cl->size;
}

void centroid_list_setIterator(CentroidList* cl, int index) {
  if (cl == NULL) {
    return;
  }

  if (index >= cl->size) {
    return;
  }

  CentroidListNode* node = cl->head;
  int counter = 0;

  while (counter < index && node != NULL) {
    counter++;
    node = node->next;
  }

  cl->current = node;
}

int getClosestIndex(CentroidList* cl, Point p) {
  if (cl == NULL) {
    return -1;
  }

  if (cl->size == 0) {
    return -1;
  }

  CentroidListNode* current = cl->head;
  int closestIndex = 0;
  int closestDistance = point_fakeDist(current->centroid.point, p);

  int index = 1;
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

  return closestIndex;
}

Centroid* centroidListGetNth(CentroidList* cl, int index) {
  if (cl == NULL) {
    return NULL;
  }

  if (index < 0 || index >= cl->size) {
    // index out of range
    return NULL;
  }

  CentroidListNode* current = cl->head;
  int counter = 0;

  while (counter < index && current != NULL) {
    counter++;
    current = current->next;
  }

  return &current->centroid;
}

void centroid_list_removeClosest(CentroidList* cl, Point p, const int radius) {
  if (cl == NULL) {
    return;
  }

  CentroidListNode* current = cl->head;
  if (current == NULL) {
    return;
  }

  int closestIndex = getClosestIndex(cl, p);
  Centroid* closestCentroid = centroidListGetNth(cl, closestIndex);
  int closestDistance = point_fakeDist(p, closestCentroid->point);

  if (closestDistance <= radius * radius) {
    centroid_list_remove(cl, closestIndex);
  }
}
