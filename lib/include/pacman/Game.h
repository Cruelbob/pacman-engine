#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>

#include "TaskQueue.h"
#include "GraphicsContext.h"
#include "GlobalTextureManager.h"

namespace pacman {
class GameScene;

class Game {
  public:
    enum class LoopResult {
        CONTINUE,
        EXIT
    };

    Game();
    ~Game();

    LoopResult loop();

    void postNextState(std::unique_ptr<GameScene>&& nextScene);
    void postExit();

    GameScene& getCurrentGameScene() { return *scene_; }
    GlobalTextureManager& getGlobalTextureManager() { return globalTextureManager_; }
  private:
    TaskQueue taskQueue_;
    std::unique_ptr<GameScene> nextScene_;
    std::unique_ptr<GameScene> scene_;
    GraphicsContext graphicsContext_;
    GlobalTextureManager globalTextureManager_;
};
} // namespace pacman

#endif // GAME_H
