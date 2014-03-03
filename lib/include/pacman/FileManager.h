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

    void loadFile(const std::string& filename, const OnFileCallback& callback);
  private:
    class LoadingInfo {
      public:
        LoadingInfo(const OnFileCallback& callback): callback_(callback) {}

        const OnFileCallback& getCallback() const { return callback_; }
        void setCallbackConnection(ScopedCallbackConnection&& callbackConnection) {
            callbackConnection_ = std::move(callbackConnection);
        }
      private:
        OnFileCallback callback_;
        ScopedCallbackConnection callbackConnection_;
    };

    typedef std::list<LoadingInfo> LoadingInfoArray;

    GameScene& gameScene_;
    LoadingInfoArray loadingFiles_;
};
} // namespace FileIO
} // namespace pacman

#endif // FILEMANAGER_H
