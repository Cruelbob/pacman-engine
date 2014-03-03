#ifndef GAME_H
#define GAME_H

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

    Graphics::GlobalTextureManager& getGlobalTextureManager() { return globalTextureManager_; }
    FileIO::GlobalFileManager& getGlobalFileManager() { return globalFileManager_; }
  private:
    Graphics::GlobalTextureManager globalTextureManager_;
    FileIO::GlobalFileManager globalFileManager_;
    GraphicsContext graphicsContext_;
    TaskQueue taskQueue_;
    std::unique_ptr<GameScene> scene_;
};
} // namespace pacman

#endif // GAME_H
