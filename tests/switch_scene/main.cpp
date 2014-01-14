#include <iostream>

#include <pacman.h>
#include <pacman/Game.h>
#include <pacman/GameScene.h>

using namespace pacman;

class SecondDummyGameScene: public GameScene {
    void initialize() {
        std::cout << "postExit from SecondDummyGameScene\n";
        getGame().postExit();
    }
};

class FirstDummyGameScene: public GameScene {
    void initialize() {
        std::cout << "postScene from FirstDummyGameScene\n";
        getGame().postNextState(std::unique_ptr<SecondDummyGameScene>(new SecondDummyGameScene));
    }
};

int pacmanInit(Game& game) {
    std::cout << "pacmanInit\n";
    game.postNextState(std::unique_ptr<FirstDummyGameScene>(new FirstDummyGameScene));
    return 0;
}
