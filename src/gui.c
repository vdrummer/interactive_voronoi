#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gui.h"

struct gui {
  int width;
  int height;
  CentroidList* centroids;
  SDL_Window* window;
  SDL_Renderer* renderer;
  bool quit;
};

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
    }
  }

  //TODO implement other update stuff
}

bool gui_doQuit(Gui* g) {
  if (g == NULL) {
    return false;
  }

  return g->quit;
}

