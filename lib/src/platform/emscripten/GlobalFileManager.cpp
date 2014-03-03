#include <emscripten/emscripten.h>
#include "pacman/GlobalFileManager.h"

using namespace pacman;
using namespace pacman::FileIO;

typedef void (*OnLoad)(void*,void*,int);
typedef void (*OnError)(void*);

ScopedCallbackConnection GlobalFileManager::loadFile(const std::string &filename, const OnFileCallback &loading)
{
    auto file = std::make_shared<LoadingFile>();
    if(!file->init(filename, loading)) {
        return ScopedCallbackConnection();
    }
    std::weak_ptr<LoadingFile> fileWeak = file;
    return CallbackConnection([fileWeak] {
        auto file = fileWeak.lock();
        if(file) {
            file->cancel();
        }
    });
}

void GlobalFileManager::LoadingFile::onLoad(std::shared_ptr<LoadingFile>* file, uint8_t *data, int size) {
    if((*file)->callback_) {
        auto callback = (*file)->callback_;
        (*file)->callback_ = nullptr;
        callback((*file)->filename_, LoadingStatus::SUCCESS, array_view<uint8_t>(data, size));
    }
    delete file;
}

void GlobalFileManager::LoadingFile::onError(std::shared_ptr<LoadingFile>* file) {
    if((*file)->callback_) {
        auto callback = (*file)->callback_;
        (*file)->callback_ = nullptr;
        callback((*file)->filename_, LoadingStatus::FAILURE, array_view<uint8_t>());
    }
    delete file;
}


GlobalFileManager::LoadingFile::~LoadingFile() {
    cancel();
}

bool GlobalFileManager::LoadingFile::init(const std::string &filename, const OnFileCallback &callback) {
    filename_ = filename;
    callback_ = callback;

    auto file = new std::shared_ptr<LoadingFile>(shared_from_this());

    emscripten_async_wget_data(filename.c_str(),
                               file,
                               reinterpret_cast<OnLoad>(&LoadingFile::onLoad),
                               reinterpret_cast<OnError>(&LoadingFile::onError));
    return true;
}

void GlobalFileManager::LoadingFile::cancel() {
    if(callback_) {
        auto callback = callback_;
        callback_ = nullptr;
        callback(filename_, LoadingStatus::CANCELED, array_view<uint8_t>());
    }
}
