#ifndef VORONOI_POINT_LIST_H
#define VORONOI_POINT_LIST_H

#include <stdlib.h>
#include "centroid.h"

struct centroid_list;
typedef struct centroid_list CentroidList;

CentroidList* centroid_list_init();
void centroid_list_free(CentroidList* pl);

void centroid_list_append(CentroidList* pl, Centroid p);
void centroid_list_remove(CentroidList* pl, size_t index);
Centroid* centroid_list_getNext(CentroidList* pl);
void centroid_list_resetIterator(CentroidList* pl);
size_t centroid_list_getSize(CentroidList* cl);

#endif // VORONOI_POINT_LIST_H
