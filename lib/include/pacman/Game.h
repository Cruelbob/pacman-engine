#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include <string>
#include <memory>

#include "TaskQueue.h"
#include "GraphicsContext.h"
#include "GlobalTextureManager.h"
#include "GlobalFileManager.h"

namespace pacman {
class GameScene;
class Game {
  public:
    Game();
    ~Game();

    bool loop();

    void postNextState(std::unique_ptr<GameScene>&& nextScene);
    void postExit();

    GlobalTextureManager& getGlobalTextureManager() { return globalTextureManager_; }
    GlobalFileManager& getGlobalFileManager() { return globalFileManager_; }
  private:
    GlobalTextureManager globalTextureManager_;
    GlobalFileManager globalFileManager_;
    GraphicsContext graphicsContext_;
    TaskQueue taskQueue_;
    std::unique_ptr<GameScene> scene_;
};
} // namespace pacman

#endif // PACMAN_GAME_H
