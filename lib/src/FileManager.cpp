#include "pacman/FileManager.h"
#include "pacman/GlobalFileManager.h"
#include "pacman/GameScene.h"
#include "pacman/Game.h"

using namespace pacman;

void FileManager::loadFileFromAddr(const std::string &filename,
                                                 const LoadingCallback &loadingCallback)
{
    std::weak_ptr<LoadingFiles> loadingFilesInfoArrWeak = loadingFilesInfoArr_;
    auto loadingFileInfoIt = loadingFilesInfoArr_->emplace(loadingFilesInfoArr_->end(), loadingCallback);
    auto localLoadingCallback = [loadingFilesInfoArrWeak,
                                 loadingFileInfoIt](const LoadingFile& loadingFile)
    {
        auto loadingFilesInfoArr = loadingFilesInfoArrWeak.lock();
        if(loadingFilesInfoArr) {
            loadingFileInfoIt->getCallback()(loadingFile);
            loadingFilesInfoArr->erase(loadingFileInfoIt);
        }
    };
    GlobalFileManager& globalFileManager = gameScene_.getGame().getGlobalFileManager();
    loadingFileInfoIt->setCallbackConnection(globalFileManager.loadFileFromAddr(filename,
                                                                                localLoadingCallback));
}
