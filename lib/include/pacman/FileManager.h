#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <list>
#include <memory>

#include "CallbackConnection.h"
#include "GlobalFileManager.h"

namespace pacman {
class GameScene;
namespace FileIO {
class FileManager {
  public:
    FileManager(GameScene& gameScene): gameScene_(gameScene) {}

    void loadFile(const std::string& filename, const LoadingCallback& loadingCallback);
  private:
    class LoadingFileInfo {
      public:
        LoadingFileInfo(const LoadingCallback& callback): callback_(callback) {}

        const LoadingCallback& getCallback() const { return callback_; }
        void setCallbackConnection(ScopedCallbackConnection&& callbackConnection) {
            callbackConnection_ = std::move(callbackConnection);
        }
      private:
        LoadingCallback callback_;
        ScopedCallbackConnection callbackConnection_;
    };

    typedef std::list<LoadingFileInfo> LoadingFiles;

    GameScene& gameScene_;
    LoadingFiles loadingFiles_;
};
} // namespace FileIO
} // namespace pacman

#endif // FILEMANAGER_H
