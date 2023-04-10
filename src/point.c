#include <stdlib.h>

#include "point.h"

Point point_random(const int min_x, const int max_x, const int min_y, const int max_y) {
  const double x = (rand() % max_x) + min_x;
  const double y = (rand() % max_y) + min_y;

  return (Point) {x, y};
}
