#ifndef GameScene_H
#define GameScene_H

#include "FileManager.h"
#include "InputManager.h"

namespace pacman {
class Game;

class GameScene {
  public:
    virtual ~GameScene() {}

    void setGame(Game* game) { game_ = game; }
    virtual void initialize() = 0;
    virtual void update() {}

    FileManager& getFileManager() { return fileManager_; }
    InputManager& getInputManager() { return inputManager_; }
    Game& getGame() const { return *game_; }
  private:
    Game* game_;
    FileManager fileManager_;
    InputManager inputManager_;
};
} // namespace pacman

#endif // GameScene_H
