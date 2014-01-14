#include <iostream>

#include <pacman.h>
#include <pacman/Game.h>
#include <pacman/GameScene.h>

using namespace pacman;

class DummyGameScene: public GameScene {
    ScopedCallbackConnection keyCallback_;
  public:
    void initialize() override {
        keyCallback_ = getInputManager().addOnKeyEvent([this](const KeyEvent& keyEvent) {
            if(keyEvent.getType() == KeyEvent::Type::DOWN && keyEvent.getKey() == KeyEvent::Key::ESC) {
                std::cout << "ESCAPE key pressed\n";
                std::cout << "postExit from DummyGameScene\n";
                getGame().postExit();
            }
        });
    }
};

int pacmanInit(Game& game) {
    std::cout << "pacmanInit\n";
    game.postNextState(std::unique_ptr<DummyGameScene>(new DummyGameScene));
    return 0;
}
