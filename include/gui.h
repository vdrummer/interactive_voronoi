#ifndef VORONOI_GUI_H
#define VORONOI_GUI_H

#include "centroid_list.h"

#include <stdbool.h>

typedef struct gui Gui;
struct gui;

Gui* gui_init(const int width, const int height, CentroidList* cl);
void gui_free(Gui* g);

void gui_render(Gui* g);
void gui_update(Gui* g);

bool gui_doQuit(Gui* g);

#endif // VORONOI_GUI_H
