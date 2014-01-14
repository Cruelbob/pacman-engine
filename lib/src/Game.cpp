#include "pacman/Game.h"
#include "pacman/GameScene.h"

using namespace pacman;

Game::Game(): globalTextureManager_(*this) {

}

Game::~Game() {

}

Game::LoopResult Game::loop() {
    if(scene_) {
#if UNIX
        scene_->getFileManager().update();
#endif
        scene_->getInputManager().update();
        scene_->update();
        graphicsContext_.update();
        taskQueue_.executeTasks(taskQueue_.getSize());
        return LoopResult::CONTINUE;
    }
    return LoopResult::EXIT;
}

void Game::postNextState(std::unique_ptr<GameScene>&& nextSceneUnique) {
    if(scene_) {
        GameScene* nextScene = nextSceneUnique.release();
        taskQueue_.post([nextScene, this] {
            scene_.reset(nextScene);
            scene_->setGame(this);
            scene_->initialize();
        });
    } else {
        scene_ = std::move(nextSceneUnique);
        scene_->setGame(this);
        scene_->initialize();
    }
}

void Game::postExit() {
    taskQueue_.post([this] {
        scene_.reset();
    });
}
