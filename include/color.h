#ifndef VORONOI_COLOR_H
#define VORONOI_COLOR_H

typedef struct color Color;
struct color {
  int r;
  int g;
  int b;
};

Color color_random();

#endif // VORONOI_COLOR_H
