#include <sys/types.h>
#include <aio.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <cassert>

#include "pacman/GlobalFileManager.h"

using namespace pacman;
using namespace FileIO;

GlobalFileManager::~GlobalFileManager() {
}

void GlobalFileManager::update()
{
    for(auto fileIt = loadingFiles_.begin(); fileIt != loadingFiles_.end();) {
        if((*fileIt)->update()) {
            ++fileIt;
        } else {
            fileIt = loadingFiles_.erase(fileIt);
        }
    }
}

ScopedCallbackConnection GlobalFileManager::loadFile(const std::string &filename, const LoadingCallback &callback) {
    auto filePtr = std::make_shared<LoadingFile>();
    if(!filePtr->init(filename, callback)) {
        return CallbackConnection();
    }
    loadingFiles_.emplace_back(filePtr);

    std::weak_ptr<LoadingFile> fileWeakPtr = filePtr;
    return CallbackConnection([fileWeakPtr] {
        auto filePtr = fileWeakPtr.lock();
        if(filePtr) {
            filePtr->cancel();
        }
    });
}

GlobalFileManager::LoadingFile::~LoadingFile() {
    cancel();
    while(update());
}

bool GlobalFileManager::LoadingFile::init(const std::string& filename, const LoadingCallback& callback) {
    int fd = open(filename.c_str(), O_RDONLY, 0);
    if (fd == -1) {
        callback(filename, LoadingStatus::FAILURE, array_view<uint8_t>());
        return false;
    }

    off_t fullSize = lseek(fd, 0, SEEK_END);
    assert(fullSize != -1);
    lseek(fd, 0, SEEK_SET);

    buffer_.resize(fullSize);
    aiocb* aiocbPtr = (aiocb*)std::malloc(sizeof(aiocb));
    std::memset(aiocbPtr, 0, sizeof(aiocb));
    aiocbPtr->aio_nbytes = fullSize;
    aiocbPtr->aio_fildes = fd;
    aiocbPtr->aio_buf = buffer_.data();
    aiocb_.reset(aiocbPtr,[](aiocb* aiocbPtr) {
        close(aiocbPtr->aio_fildes);
        std::free(aiocbPtr);
    });

    assert(aio_read(aiocb_.get()) != -1);

    filename_ = filename;
    callback_ = callback;

    return true;
}

bool GlobalFileManager::LoadingFile::update() {
    bool inProgress = false;
    if(aiocb_) {
        int err =  aio_error(aiocb_.get());
        switch(err) {
          case EINPROGRESS:
            inProgress = true;
            break;
          case 0:
            aiocb_.reset();
            if(callback_) {
                callback_(filename_, LoadingStatus::SUCCESS, buffer_);
            }
            break;
          default:
            aiocb_.reset();
            if(callback_) {
                callback_(filename_, LoadingStatus::FAILURE, array_view<uint8_t>());
            }
            break;
        };
    }
    return inProgress;
}

void GlobalFileManager::LoadingFile::cancel() {
    if(aiocb_) {
        int err = aio_cancel(aiocb_->aio_fildes, aiocb_.get());
        if(err == AIO_CANCELED) {
            aiocb_.reset();
        }
        callback_(filename_, LoadingStatus::CANCELED, array_view<uint8_t>());
        callback_ = nullptr;
    }
}
