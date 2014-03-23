#ifndef GLOBALFILEMANAGER_H
#define GLOBALFILEMANAGER_H

#include <functional>
#include <vector>
#include <cstdint>
#include <list>
#include <string>
#include <memory>

#include "pacman/Config.h"

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
                            const array_view<uint8_t>&) /* fileData */> OnFileCallback;

class GlobalFileManager {
  public:
    GlobalFileManager() = default;
    ~GlobalFileManager() = default;

#if UNIX
    void update();
#endif

    ScopedCallbackConnection loadFile(const std::string& filename, const OnFileCallback& callback);
  private:
    class LoadingFile: public std::enable_shared_from_this<LoadingFile> {
      public:
        LoadingFile() = default;
        ~LoadingFile();

        bool init(const std::string& filename, const OnFileCallback& callback);
        void cancel();
#if UNIX
        bool update();
#endif
      private:
        std::string filename_;
        OnFileCallback callback_;

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
