#include "pacman.h"
#include "pacman/Game.h"

using namespace pacman;

int main() {
    Game game;
    int res = pacmanInit(game);
    if(res) {
        return res;
    }
    while(game.loop());
    return 0;
}
