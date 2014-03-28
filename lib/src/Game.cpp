#include "pacman/Game.h"
#include "pacman/GameScene.h"

using namespace pacman;

Game::Game(): globalTextureManager_(*this) {

}

Game::~Game() {

}

bool Game::loop() {
    if(scene_) {
#if UNIX
        globalFileManager_.update();
#endif
        scene_->getInputManager().update();
        scene_->visit(Time(0));
        graphicsContext_.update();
        taskQueue_.executeTasks(taskQueue_.getSize());
        return true;
    } else {
        return false;
    }
}

void Game::postNextState(std::unique_ptr<GameScene>&& nextScene) {
    if(scene_) {
        GameScene * nextSceneRawPtr = nextScene.release();
        taskQueue_.post([this, nextSceneRawPtr] {
            scene_.reset();
            postNextState(std::unique_ptr<GameScene>(nextSceneRawPtr));
        });
    } else {
        scene_ = std::move(nextScene);
        scene_->setGame(this);
        scene_->initialize();
    }
}

void Game::postExit() {
    taskQueue_.post([this] {
        scene_.reset();
    });
}
