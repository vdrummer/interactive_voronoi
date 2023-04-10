#include <stdlib.h>

#include "point.h"

Point point_random(const int min_x, const int max_x, const int min_y, const int max_y) {
  const double x = (rand() % max_x) + min_x;
  const double y = (rand() % max_y) + min_y;

  return (Point) {x, y};
}

int point_fakeDist(Point p1, Point p2) {
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return dx * dx + dy * dy;
}
