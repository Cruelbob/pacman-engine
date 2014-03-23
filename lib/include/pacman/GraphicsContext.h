#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#include "pacman/Config.h"

#if SDL == 1
#include <SDL/SDL.h>
#elif SDL == 2
#include <SDL2/SDL.h>
#endif

namespace pacman {
class GraphicsContext {
  public:
    GraphicsContext();
    ~GraphicsContext();

    void update();
  private:
#if SDL == 1
    SDL_Surface* screen_;
#elif SDL == 2
    SDL_Window* window_;
    SDL_GLContext glContext_;
#endif
};
} // namespace pacman

#endif // GRAPHICSCONTEXT_H
