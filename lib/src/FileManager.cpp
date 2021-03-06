#include "pacman/FileManager.h"
#include "pacman/GlobalFileManager.h"
#include "pacman/GameScene.h"
#include "pacman/Game.h"

using namespace pacman;

void FileManager::loadFile(const std::string &filename, const OnFileCallback &callback) {
    auto localInfoIt = loadingFiles_.emplace(loadingFiles_.end(), callback);
    auto localCallback =
    [this,localInfoIt](const std::string& filename, LoadingStatus status, const array_view<uint8_t>& buffer) {
        localInfoIt->getCallback()(filename, status, buffer);
        if(status != LoadingStatus::CANCELED) {
            loadingFiles_.erase(localInfoIt);
        }
    };
    ScopedCallbackConnection connection = gameScene_.getGame().getGlobalFileManager().loadFile(filename, localCallback);
    if(connection.connected()) {
        localInfoIt->setCallbackConnection(std::move(connection));
    }
}
