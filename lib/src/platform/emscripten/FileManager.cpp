#include <emscripten/emscripten.h>
#include "pacman/FileManager.h"

using namespace pacman;

typedef void (*OnLoad)(void*,void*,int);
typedef void (*OnError)(void*);

class FileManager::EmscriptenLoadingInfo  {
  public:
      EmscriptenLoadingInfo(const std::weak_ptr<LoadingFiles>& loadingFiles,
                            const LoadingFiles::iterator& loadingFileInfoIt):
          loadingFiles_(loadingFiles),
          loadingFileInfoIt_(loadingFileInfoIt) {}

      const std::weak_ptr<LoadingFiles>& getLoadingFiles() { return loadingFiles_; }
      const LoadingFiles::iterator& getLoadingFileInfoIt() const { return loadingFileInfoIt_; }
  private:
      std::weak_ptr<LoadingFiles> loadingFiles_;
      LoadingFiles::iterator loadingFileInfoIt_;
};


void FileManager::loadFileFromAddr(const std::string &filename, const LoadingCallback &loadingCallback)
{
    auto loadingFileInfoIt = loadingFiles_->emplace(loadingFiles_->end(), filename, loadingCallback);
    auto emscriptenLoadingInfo = new EmscriptenLoadingInfo(loadingFiles_, loadingFileInfoIt);
    emscripten_async_wget_data(filename.c_str(),
                               emscriptenLoadingInfo,
                               reinterpret_cast<OnLoad>(&FileManager::onLoad),
                               reinterpret_cast<OnError>(&FileManager::onError));
}

void FileManager::onLoad(EmscriptenLoadingInfo *emscriptenLoadingInfo, uint8_t *data, int size)
{
    auto loadingFiles = emscriptenLoadingInfo->getLoadingFiles().lock();
    if(loadingFiles) {
        LoadingFiles::iterator loadingFileInfoIt = emscriptenLoadingInfo->getLoadingFileInfoIt();
        LoadingFileInfo& loadingFileInfo = *loadingFileInfoIt;
        loadingFileInfo.getFile().getBuffer().assign(data,data+size);
        loadingFileInfo.getFile().setStatus(LoadingStatus::SUCCESS);
        loadingFileInfo.getLoadingCallback()(loadingFileInfo.getFile());
        loadingFiles->erase(loadingFileInfoIt);
    }
    delete emscriptenLoadingInfo;
}

void FileManager::onError(EmscriptenLoadingInfo *emscriptenLoadingInfo)
{
    auto loadingFiles = emscriptenLoadingInfo->getLoadingFiles().lock();
    if(loadingFiles) {
        LoadingFiles::iterator loadingFileInfoIt = emscriptenLoadingInfo->getLoadingFileInfoIt();
        LoadingFileInfo& loadingFileInfo = *loadingFileInfoIt;
        loadingFileInfo.getFile().setStatus(LoadingStatus::FAILURE);
        loadingFileInfo.getLoadingCallback()(loadingFileInfo.getFile());
        loadingFiles->erase(loadingFileInfoIt);
    }
    delete emscriptenLoadingInfo;
}
