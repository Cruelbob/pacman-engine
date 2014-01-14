#include <iostream>

#include <pacman.h>
#include <pacman/Game.h>
#include <pacman/GameScene.h>

using namespace pacman;

class DummyGameScene: public GameScene {
    void initialize() {
        std::cout << "postExit from DummyGameScene\n";
        getGame().postExit();
    }
};

int pacmanInit(Game& game) {
    std::cout << "pacmanInit\n";
    game.postNextState(std::unique_ptr<DummyGameScene>(new DummyGameScene));
    return 0;
}
