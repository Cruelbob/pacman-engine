#include "pacman/FileManager.h"
#include "pacman/GlobalFileManager.h"
#include "pacman/GameScene.h"
#include "pacman/Game.h"

using namespace pacman;
using namespace FileIO;

void FileManager::loadFile(const std::string &filename, const LoadingCallback &loadingCallback) {
    auto localInfoIt = loadingFiles_.emplace(loadingFiles_.end(), loadingCallback);
    auto localCallback =
    [this,localInfoIt](const std::string& filename, LoadingStatus status, const array_view<uint8_t>& buffer) {
        localInfoIt->getCallback()(filename, status, buffer);
        if(status != LoadingStatus::CANCELED) {
            loadingFiles_.erase(localInfoIt);
        }
    };
    localInfoIt->setCallbackConnection(gameScene_.getGame().getGlobalFileManager().loadFile(filename, localCallback));
}
