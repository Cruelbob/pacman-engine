#include <iostream>
#include <emscripten/emscripten.h>

#include "pacman.h"
#include "pacman/Game.h"

using namespace pacman;

std::unique_ptr<Game> game;

void mainLoop() {
    if(!game->loop()) {
        game.reset();
        emscripten_cancel_main_loop();
    }
}

int main() {
    game.reset(new Game());
    int res = pacmanInit(*game);
    if(res)
    {
        return res;
    }
    emscripten_set_main_loop(mainLoop, 0, 0);
    return 0;
}
