#include <iostream>

#include <pacman.h>
#include <pacman/GameScene.h>
#include <pacman/Game.h>
#include <pacman/Texture.h>
#include <pacman/Sprite.h>

using namespace pacman;

const std::string IMAGE_FILE = "bender.png";

class DummyGameScene: public GameScene {
    std::shared_ptr<Texture> texture_;
    std::shared_ptr<Sprite> sprite_;

    void initialize() override {
        getInputManager().addOnKeyEvent([this](const KeyEvent& keyEvent) {
            if(keyEvent.getType() == KeyEvent::Type::DOWN && keyEvent.getKey() == KeyEvent::Key::ESC) {
                getGame().postExit();
            }
        });

        texture_ = getGame().getGlobalTextureManager().getTexture(IMAGE_FILE);
    }
    void update(Time deltaTime) {
        if(!sprite_ && texture_->isInitialized()) {
            std::cout << "texture loaded\n";
            sprite_ = std::make_shared<Sprite>(texture_);
        }
        GameScene::update(deltaTime);
    }
};

int pacmanInit(Game& game) {
    std::cout << "pacmanInit\n";
    game.postNextState(std::unique_ptr<DummyGameScene>(new DummyGameScene));
    return 0;
}
