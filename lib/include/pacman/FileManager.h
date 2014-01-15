#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <list>
#include <functional>
#include <memory>

#include "CallbackConnection.h"
#include "pacman/GlobalFileManager.h"

namespace pacman {
class GameScene;
class FileManager {
  public:
    typedef GlobalFileManager::LoadingCallback LoadingCallback;

    FileManager(GameScene& gameScene): gameScene_(gameScene) {}

    void setBase(const std::string& base) { base_ = base; }
    void loadFileFromAddr(const std::string& filename, const LoadingCallback& loadingCallback);
    void loadFile(const std::string& filename, const LoadingCallback& loadingCallback) {
        loadFileFromAddr(base_ + filename, loadingCallback);
    }
  private:
    std::string base_;

    class LoadingFileInfo {
      public:
        LoadingFileInfo(const LoadingCallback& callback): callback_(callback) {}

        const LoadingCallback& getCallback() { return callback_; }
        void setCallbackConnection(ScopedCallbackConnection&& callbackConnection) {
            callbackConnection_ = std::move(callbackConnection);
        }
      private:
        const LoadingCallback callback_;
        ScopedCallbackConnection callbackConnection_;
    };

    typedef std::list<LoadingFileInfo> LoadingFiles;

    std::shared_ptr<LoadingFiles> loadingFilesInfoArr_;

    GameScene& gameScene_;
};
}

#endif // FILEMANAGER_H
