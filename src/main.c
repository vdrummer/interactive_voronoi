#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "gui.h"
#include "centroid_list.h"

#define WIDTH 800
#define HEIGHT 600

int main() {
  CentroidList* centroids = centroid_list_init();
  assert(centroids != NULL);

  Gui* gui = gui_init(WIDTH, HEIGHT, centroids);
  assert(gui != NULL);

  while (!gui_doQuit(gui)) {
    gui_update(gui);
    gui_render(gui);
  }

  gui_free(gui);
  centroid_list_free(centroids);

  return 0;
}
