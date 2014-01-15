#ifndef GLOBALFILEMANAGER_H
#define GLOBALFILEMANAGER_H

#include <functional>
#include <vector>
#include <cstdint>
#include <list>
#include <string>
#include <memory>

#if UNIX
#include <aio.h>
#include <unistd.h>
#endif

#include "array_view.h"
#include "CallbackConnection.h"

namespace pacman {
class LoadingFile {
  public:
    enum class LoadingStatus {
        SUCCESS,
        FAILURE,
        CANCELED
    };

    typedef array_view<uint8_t> BufferView;

    LoadingFile() = delete;
    LoadingFile(const LoadingFile&) = delete;
    LoadingFile& operator=(const LoadingFile&) = delete;

    LoadingFile(const std::string& filename,
                LoadingStatus loadingStatus,
                const BufferView& bufferView = BufferView()):
        filename_(filename),
        loadingStatus_(loadingStatus),
        bufferView_(bufferView) {}

    const std::string& getFilename() const { return filename_; }
    LoadingStatus getStatus() const { return loadingStatus_; }
    const BufferView& getBufferView() const { return bufferView_; }
  private:
    const std::string& filename_;
    const LoadingStatus loadingStatus_;
    const BufferView bufferView_;
};

class GlobalFileManager {
  public:
    typedef std::function<void (const LoadingFile&)> LoadingCallback;

    GlobalFileManager(): loadingFiles_(std::make_shared<LoadingFiles>()) {}

    void update();

    ScopedCallbackConnection loadFileFromAddr(const std::string& filename, const LoadingCallback& loadingCallback);
  private:
    class LoadingFileInfo {
      public:
        class PlatformInfo {
          public:
            PlatformInfo()
        #if UNIX
            : aiocb_({}) {}
        #elif EMSCRIPTEN
            {}
        #endif

        #if UNIX
            aiocb& get_aiocb() { return aiocb_; }
        #endif
          private:
        #if UNIX
            aiocb aiocb_; //TODO: close file
        #endif
        };

        LoadingFileInfo(const std::string& filename, const LoadingCallback& callback):
            filename_(filename), callback_(callback) {}

        PlatformInfo& getPlatformInfo() {return platformInfo_; }

        const std::string& getFilename() const { return filename_; }
        const LoadingCallback& getCallback() const { return callback_; }
      private:
        const std::string filename_;
        const LoadingCallback callback_;
        LoadingFile::LoadingStatus status;
        PlatformInfo platformInfo_;
    };

    typedef std::list<LoadingFileInfo> LoadingFiles;

    std::shared_ptr<LoadingFiles> loadingFiles_;

#if EMSCRIPTEN
    typedef std::weak_ptr<LoadingFiles::iterator> EmscriptenLoadingFileInfo;

    static void onLoad(EmscriptenLoadingFileInfo* loadingFileInfo, uint8_t* data, int size);
    static void onError(EmscriptenLoadingFileInfo* loadingFileInfo);
#endif
};
} // namespace pacman

#endif // GLOBALFILEMANAGER_H
