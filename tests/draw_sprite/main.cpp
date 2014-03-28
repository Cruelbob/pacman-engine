#include <iostream>
#include <functional>

#include <pacman.h>
#include <pacman/GameScene.h>
#include <pacman/Game.h>
#include <pacman/Texture.h>
#include <pacman/Sprite.h>

using namespace pacman;
using namespace pacman::Graphics;

const std::string IMAGE_FILE = "bender.png";

class DummyGameScene: public GameScene {
    ScopedCallbackConnection keyCallback_;

    void initialize() override {
        keyCallback_ = getInputManager().addOnKeyEvent([this](const KeyEvent& keyEvent) {
            if(keyEvent.getType() == KeyEvent::Type::DOWN && keyEvent.getKey() == KeyEvent::Key::ESC) {
                getGame().postExit();
            }
        });

        addChild(std::make_shared<Sprite>(getGame().getGlobalTextureManager().getTexture(IMAGE_FILE)));
    }
};

int pacmanInit(Game& game) {
    std::cout << "pacmanInit\n";
    game.postNextState(std::unique_ptr<DummyGameScene>(new DummyGameScene));
    return 0;
}
