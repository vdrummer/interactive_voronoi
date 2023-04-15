#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gui.h"
#include "point.h"
#include "centroid.h"
#include "centroid_list.h"

#define RADIUS 10

struct gui {
  int width;
  int height;
  CentroidList* centroids;
  SDL_Window* window;
  SDL_Renderer* renderer;
  bool quit;
  Centroid* currentCentroid;
};

// INTERNAL FUNCTIONS

void renderCentroid(Gui* g, Centroid c, int r) {
  int x0 = c.point.x - r;
  int y0 = c.point.y - r;
  int x1 = c.point.x + r;
  int y1 = c.point.y + r;

  SDL_SetRenderDrawColor(g->renderer, 255, 255, 255, 255);

  for (int y = y0; y < y1; y++) {
    if (y >= 0 && y < g->height) {
      for (int x = x0; x < x1; x++) {
        if (x >= 0 && x < g->width) {
          if (point_fakeDist((Point) {x, y}, c.point) < r * r) {
            SDL_RenderDrawPoint(g->renderer, x, y);
          }
        }
      }
    }
  }
}

// EXTERNAL FUNCTIONS

Gui* gui_init(const int width, const int height, CentroidList* cl) {
  Gui* gui = malloc(sizeof(Gui));
  if (gui == NULL) {
    return NULL;
  }

  gui->width = width;
  gui->height = height;
  gui->centroids = cl;
  gui->quit = false;
  gui->currentCentroid = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error intiializing SDL: %s\n", SDL_GetError());
    exit(1);
  }

  gui->window = SDL_CreateWindow("Interactive Voronoi", 0, 0, gui->width, gui->height, 0);
  if (!gui->window) {
    fprintf(stderr, "Error intiializing SDL Window: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  gui->renderer = SDL_CreateRenderer(gui->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!gui->renderer) {
    fprintf(stderr, "Error intiializing SDL Renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(gui->window);
    SDL_Quit();
    exit(1);
  }

  return gui;
}

void gui_free(Gui* g) {
  if (g == NULL) {
    return;
  }

  SDL_DestroyRenderer(g->renderer);
  SDL_DestroyWindow(g->window);
  SDL_Quit();
}

void gui_render(Gui* g) {
  if (g == NULL) {
    return;
  }

  SDL_SetRenderDrawColor(g->renderer, 255, 255, 255, 255);
  SDL_RenderClear(g->renderer);

  // voronoi rendering
  for (int x = 0; x < g->width; x++) {
    for (int y = 0; y < g->height; y++) {
      Centroid* c = centroid_list_getClosestCentroid(g->centroids, (Point) {x, y});
      if (c == NULL) {
        continue;
      }

      SDL_SetRenderDrawColor(g->renderer, c->color.r, c->color.g, c->color.b, 255);
      SDL_RenderDrawPoint(g->renderer, x, y);
    }
  }

  // centroid rendering
  centroid_list_resetIterator(g->centroids);
  Centroid* cp = centroid_list_getNext(g->centroids);

  while (cp != NULL) {
    renderCentroid(g, *cp, RADIUS);
    cp = centroid_list_getNext(g->centroids);
  }

  SDL_RenderPresent(g->renderer);
}

void gui_update(Gui* g) {
  if (g == NULL) {
    return;
  }

  // event handling
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch(e.type) {
      case SDL_QUIT:
        g->quit = true;
        break;
      case SDL_MOUSEBUTTONUP:
        if (g->currentCentroid == NULL) {
          const Point clickedPoint = {e.button.x, e.button.y};
          if (e.button.button == SDL_BUTTON_LEFT) {
            centroid_list_append(
                g->centroids,
                (Centroid) {
                  .point = clickedPoint,
                  .color = color_random()
                }
            );
          } else if (e.button.button == SDL_BUTTON_RIGHT) {
            centroid_list_removeClosest(g->centroids, clickedPoint, RADIUS);
          }
        } else {
          g->currentCentroid = NULL;
        }
        break;
      case SDL_MOUSEMOTION:
        if (e.motion.state & SDL_BUTTON_LMASK) {
          Point clickedPoint = {e.motion.x, e.motion.y};
          Centroid* closestCentroid = centroid_list_getClosestCentroid(g->centroids, clickedPoint);
          if (closestCentroid != NULL) {
            if (g->currentCentroid == NULL) {
              if (point_fakeDist(clickedPoint, closestCentroid->point) < RADIUS * RADIUS) {
                g->currentCentroid = closestCentroid;
              }
            } else {
              g->currentCentroid->point = clickedPoint;
            }
          }
        }
        break;
    }
  }
}

bool gui_doQuit(Gui* g) {
  if (g == NULL) {
    return false;
  }

  return g->quit;
}

