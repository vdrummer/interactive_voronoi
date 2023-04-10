#ifndef VORONOI_POINT_LIST_H
#define VORONOI_POINT_LIST_H

#include <stdlib.h>

#include "centroid.h"
#include "point.h"

struct centroid_list;
typedef struct centroid_list CentroidList;

CentroidList* centroid_list_init();
void centroid_list_free(CentroidList* cl);

void centroid_list_append(CentroidList* cl, Centroid c);
void centroid_list_remove(CentroidList* cl, size_t index);
Centroid* centroid_list_getNext(CentroidList* cl);
void centroid_list_resetIterator(CentroidList* cl);
void centroid_list_setIterator(CentroidList* cl, size_t index);
size_t centroid_list_getSize(CentroidList* cl);
void centroid_list_removeClosest(CentroidList* cl, Point p, const int radius);

#endif // VORONOI_POINT_LIST_H
