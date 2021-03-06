#include "pacman/Config.h"

#if SDL == 1
#include <SDL/SDL.h>
#elif SDL == 2
#include <SDL2/SDL.h>
#endif

#include "pacman/InputManager.h"

using namespace pacman;

void InputManager::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
          case SDL_KEYDOWN:
            switch(event.key.keysym.scancode) {
              case SDL_SCANCODE_ESCAPE:
                for(auto& keyEventCallback : keyEventCallbacks_) {
                    keyEventCallback(KeyEvent(KeyEvent::Type::DOWN, KeyEvent::Key::ESC));
                }
              default:
                break;
            }
          default:
            break;
        }
    }
}
