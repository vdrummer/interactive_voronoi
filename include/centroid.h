#ifndef VORONOI_CENTROID_H
#define VORONOI_CENTROID_H

#include "point.h"
#include "color.h"

typedef struct centroid Centroid;
struct centroid {
  Point point;
  Color color;
};

#endif // VORONOI_CENTROID_H
