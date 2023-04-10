#include <stdlib.h>

#include "color.h"

Color color_random() {
  Color c;

  c.r = rand() % 255;
  c.g = rand() % 255;
  c.b = rand() % 255;

  return c;
}
