#include <iostream>
#include <functional>

#include <pacman.h>
#include <pacman/GameScene.h>
#include <pacman/Game.h>
#include <pacman/Texture.h>

using namespace pacman;
using namespace pacman::Graphics;

const std::string IMAGE_FILE = "bender.png";

class DummyGameScene: public GameScene {
    std::shared_ptr<Texture> texture_;
    void initialize() override {
        texture_ = getGame().getGlobalTextureManager().getTexture(IMAGE_FILE);
    }

    void update() override {
        if(texture_->isInitialized()) {
            std::cout << "texture: " << texture_->getWidth() << "x" << texture_->getHeight() << "\n";
            std::cout << "postExit from DummyGameScene\n";
            getGame().postExit();
        }
    }
};

int pacmanInit(Game& game) {
    std::cout << "pacmanInit\n";
    game.postNextState(std::unique_ptr<DummyGameScene>(new DummyGameScene));
    return 0;
}
