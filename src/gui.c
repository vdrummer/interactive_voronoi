#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gui.h"
#include "point.h"

#define RADIUS 10

struct gui {
  int width;
  int height;
  CentroidList* centroids;
  SDL_Window* window;
  SDL_Renderer* renderer;
  bool quit;
};

// INTERNAL FUNCTIONS

void renderCentroid(Gui* g, Centroid c, int r) {
  int x0 = c.point.x - r;
  int y0 = c.point.y - r;
  int x1 = c.point.x + r;
  int y1 = c.point.y + r;

  SDL_SetRenderDrawColor(g->renderer, c.color.r, c.color.g, c.color.b, 255);

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
      case SDL_MOUSEBUTTONDOWN:
        centroid_list_append(
            g->centroids,
            (Centroid) {
              .point = {e.button.x, e.button.y}, 
              .color = color_random()
            }
        );
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

