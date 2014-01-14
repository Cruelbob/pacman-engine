#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

#if SDL2
#include <SDL2/SDL.h>
#elif SDL
#include <SDL/SDL.h>
#endif

namespace pacman {
class GraphicsContext {
  public:
    GraphicsContext();
    ~GraphicsContext();

    void update();
  private:
#if SDL2
    SDL_Window* window_;
    SDL_GLContext glContext_;
#elif SDL
    SDL_Surface* screen_;
#endif
};
} // namespace pacman

#endif // GRAPHICSCONTEXT_H
