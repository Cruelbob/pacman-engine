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
namespace FileIO {
enum class LoadingStatus {
    SUCCESS,
    FAILURE,
    CANCELED
};

typedef std::function<void (const std::string& /* filename */,
                            LoadingStatus /* status */,
                            const array_view<uint8_t>&) /* fileData */> LoadingCallback;

class GlobalFileManager {
  public:
    GlobalFileManager() = default;
#ifdef UNIX
    ~GlobalFileManager();
#elif EMSCRIPTEN
    ~GlobalFileManager() = default;
#endif

#if UNIX
    void update();
#endif

    ScopedCallbackConnection loadFile(const std::string& filename, const LoadingCallback& loadingCallback);
  private:
    class LoadingFile: public std::enable_shared_from_this<LoadingFile> {
      public:
        LoadingFile()
#if UNIX
          : aiocb_(nullptr)
#endif
        {}

        ~LoadingFile();

        bool init(const std::string& filename, const LoadingCallback& callback);
        void cancel();
#if UNIX
        bool update();
#endif
      private:
        std::string filename_;
        LoadingCallback callback_;

#if UNIX
        std::shared_ptr<aiocb> aiocb_;
        std::vector<uint8_t> buffer_;
#elif EMSCRIPTEN
        static void onLoad(std::shared_ptr<LoadingFile>* file, uint8_t* data, int size);
        static void onError(std::shared_ptr<LoadingFile>* file);
#endif
    };

#if UNIX
    typedef std::list<std::shared_ptr<LoadingFile>> LoadingFiles;

    LoadingFiles loadingFiles_;
#endif
};
} // namespace FileIO
} // namespace pacman

#endif // GLOBALFILEMANAGER_H
