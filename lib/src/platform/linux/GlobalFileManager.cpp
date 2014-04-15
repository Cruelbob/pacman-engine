#include <sys/types.h>
#include <aio.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <cassert>

#include "pacman/GlobalFileManager.h"

using namespace pacman;

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

ScopedCallbackConnection GlobalFileManager::loadFile(const std::string &filename, const OnFileCallback &callback) {
    auto filePtr = std::make_shared<LoadingFile>();
    if(!filePtr->init(filename, callback)) {
        return ScopedCallbackConnection();
    }
    std::weak_ptr<LoadingFile> fileWeakPtr = filePtr;
    loadingFiles_.emplace_back(std::move(filePtr));
    return ScopedCallbackConnection([fileWeakPtr] {
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

bool GlobalFileManager::LoadingFile::init(const std::string& filename, const OnFileCallback& callback) {
    int fd = open(filename.c_str(), O_RDONLY, 0);
    if (fd == -1) {
        callback(filename, LoadingStatus::FAILURE, array_view<uint8_t>());
        return false;
    }

    off_t fullSize = lseek(fd, 0, SEEK_END);
    if(fullSize == -1) {
        callback(filename, LoadingStatus::FAILURE, array_view<uint8_t>());
        close(fd);
        return false;
    }
    lseek(fd, 0, SEEK_SET);

    buffer_.resize(fullSize);
    aiocb* aiocbPtr = (aiocb*)std::malloc(sizeof(aiocb));
    std::memset(aiocbPtr, 0, sizeof(aiocb));
    aiocbPtr->aio_fildes = fd;
    aiocbPtr->aio_nbytes = fullSize;
    aiocbPtr->aio_buf = buffer_.data();
    aiocbPtr->aio_offset = 0;
    aiocb_.reset(aiocbPtr,[](aiocb* aiocbPtr) {
        close(aiocbPtr->aio_fildes);
        std::free(aiocbPtr);
    });

    int err = aio_read(aiocb_.get());
    if(err) {
        callback(filename, LoadingStatus::FAILURE, array_view<uint8_t>());
        return false;
    }

    filename_ = filename;
    callback_ = callback;

    return true;
}

bool GlobalFileManager::LoadingFile::update() {
    if(aiocb_) {
        int err =  aio_error(aiocb_.get());
        if(err == EINPROGRESS) {
            return true;
        } else {
            ssize_t res = aio_return(aiocb_.get());
            aiocb_.reset();
            if(callback_) {
                if(res == static_cast<ssize_t>(buffer_.size())) {
                    callback_(filename_, LoadingStatus::SUCCESS, buffer_);
                } else {
                    callback_(filename_, LoadingStatus::FAILURE, array_view<uint8_t>());
                }
            }
        }
    }
    return false;
}

void GlobalFileManager::LoadingFile::cancel() {
    if(aiocb_) {
        int err = aio_cancel(aiocb_->aio_fildes, aiocb_.get());
        if(err == AIO_CANCELED) {
            aiocb_.reset();
        }
        if(callback_) {
            callback_(filename_, LoadingStatus::CANCELED, array_view<uint8_t>());
            callback_ = nullptr;
        }
    }
}
