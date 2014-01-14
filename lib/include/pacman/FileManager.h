#ifndef FILEMANAGER_H
#define FILEMANAGER_H

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
class FileManager {
  public:
    enum class LoadingStatus {
        SUCCESS,
        FAILURE,
        CANCELED
    };

    class LoadingFile {
      public:
        typedef array_view<uint8_t> BufferView;

        LoadingFile() = delete;
        LoadingFile(const LoadingFile&) = delete;
        LoadingFile& operator=(const LoadingFile&) = delete;

        LoadingFile(const std::string& filename,
                    const BufferView& bufferView = BufferView(),
                    LoadingStatus loadingStatus = LoadingStatus::FAILURE):
            filename_(filename),
            bufferView_(bufferView),
            loadingStatus_(loadingStatus) {}

        const std::string& getFilename() const { return filename_; }
        LoadingStatus getStatus() const { return loadingStatus_; }
        const BufferView& getBufferView() const { return bufferView_; }
      private:
        const std::string& filename_;
        const BufferView bufferView_;
        LoadingStatus loadingStatus_;
    };
    typedef std::function<void (const LoadingFile&)> LoadingCallback;

    FileManager(): loadingFiles_(std::make_shared<LoadingFiles>()) {}
    ~FileManager();

#if UNIX
    void update();
#endif

    void setBase(const std::string& base) { base_ = base; }
    CallbackConnection loadFileFromAddr(const std::string& filename, const LoadingCallback& loadingCallback);
    CallbackConnection loadFile(const std::string& filename, const LoadingCallback& loadingCallback) {
        return loadFileFromAddr(base_ + filename, loadingCallback);
    }

  private:
    std::string base_;

    class LoadingFileInfo {
      public:
        LoadingFileInfo(const std::string& filename, const LoadingCallback& loadingCallback):
            filename_(filename), loadingCallback_(loadingCallback)
#if UNIX
            ,fd_(-1), aiocb_{0}
#endif
        {}

#if UNIX
        typedef std::vector<uint8_t> Buffer;

        int get_fd() const { return fd_; }
        void set_fd(int fd) { fd_ = fd; }
        aiocb& get_aiocb() { return aiocb_; }
        Buffer& getBuffer() { return buffer_; }
#endif
        const std::string& getFilename() const { return filename_; }
        const LoadingCallback& getLoadingCallback() const { return loadingCallback_; }
      private:
        const std::string filename_;
        const LoadingCallback loadingCallback_;
#if UNIX
        Buffer buffer_;
        int fd_;
        aiocb aiocb_;
#endif
    };

    typedef std::list<LoadingFileInfo> LoadingFiles;

    std::shared_ptr<LoadingFiles> loadingFiles_;

#if EMSCRIPTEN
    class EmscriptenLoadingInfo  {
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

    static void onLoad(EmscriptenLoadingInfo *emscriptenLoadingInfo, uint8_t* data, int size);
    static void onError(EmscriptenLoadingInfo *emscriptenLoadingInfo);
#endif
};
} // namespace pacman

#endif // FILEMANAGER_H
