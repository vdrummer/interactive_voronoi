#ifndef VORONOI_POINT_LIST_H
#define VORONOI_POINT_LIST_H

#include <stdlib.h>
#include "point.h"

struct point_list;
typedef struct point_list PointList;

PointList* point_list_init();
void point_list_free(PointList* pl);

void point_list_append(PointList* pl, Point p);
void point_list_remove(PointList* pl, size_t index);
Point* point_list_getNext(PointList* pl);
void point_list_resetIterator(PointList* pl);

#endif // VORONOI_POINT_LIST_H
