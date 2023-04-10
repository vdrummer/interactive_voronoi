#ifndef VORONOI_POINT_H
#define VORONOI_POINT_H

typedef struct point Point;
struct point {
  double x;
  double y;
} ;

Point point_random(const int min_x, const int max_x, const int min_y, const int max_y);
int point_fakeDist(Point p1, Point p2);

#endif // VORONOI_POINT_H
