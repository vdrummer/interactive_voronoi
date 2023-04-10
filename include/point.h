#ifndef VORONOI_POINT_H
#define VORONOI_POINT_H

typedef struct point Point;
struct point {
  double x;
  double y;
} ;

Point point_random(const int min_x, const int max_x, const int min_y, const int max_y);

#endif // VORONOI_POINT_H
