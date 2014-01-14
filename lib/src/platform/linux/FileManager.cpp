#include <sys/types.h>
#include <aio.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <cassert>

#include "pacman/FileManager.h"

using namespace pacman;

FileManager::~FileManager()
{
    for(auto& loadingFileInfo : *loadingFiles_) {
        aio_cancel(loadingFileInfo.get_fd(), &loadingFileInfo.get_aiocb());
    }
    while(!loadingFiles_->empty());
}

void FileManager::update()
{
    for(LoadingFiles::iterator loadingFileInfoIt = loadingFiles_->begin();
        loadingFileInfoIt != loadingFiles_->end();)
    {
        LoadingFiles::iterator tempIt = loadingFileInfoIt++;
        LoadingFileInfo& loadingFileInfo = *tempIt;
        int err = aio_error(&loadingFileInfo.get_aiocb());

        if(err == EINPROGRESS) {
            continue;
        }

        LoadingStatus loadingStatus = LoadingStatus::SUCCESS;
        if(err == ECANCELED) {
            loadingStatus = LoadingStatus::CANCELED;
        }
        assert(err == 0);
        aio_return(&loadingFileInfo.get_aiocb());
        LoadingFile loadingFile(loadingFileInfo.getFilename(), loadingFileInfo.getBuffer(), loadingStatus);
        loadingFileInfo.getLoadingCallback()(loadingFile);
        loadingFiles_->erase(tempIt);
    }
}

CallbackConnection FileManager::loadFileFromAddr(const std::string &filename, const LoadingCallback &loadingCallback) {
    int fd = open(filename.c_str(), O_RDONLY, 0);
    if (fd == -1) {
        loadingCallback(LoadingFile(filename));
        return CallbackConnection();
    }

    off_t fullSize = lseek(fd, 0, SEEK_END);
    assert(fullSize != -1);
    lseek(fd, 0, SEEK_SET);

    auto loadingFileInfoIt = loadingFiles_->emplace(loadingFiles_->end(), filename, loadingCallback);

    loadingFileInfoIt->set_fd(fd);
    loadingFileInfoIt->getBuffer().resize(fullSize);

    loadingFileInfoIt->get_aiocb().aio_nbytes = fullSize;
    loadingFileInfoIt->get_aiocb().aio_fildes = fd;
    loadingFileInfoIt->get_aiocb().aio_buf = loadingFileInfoIt->getBuffer().data();

    assert(aio_read(&loadingFileInfoIt->get_aiocb()) != -1);

    std::weak_ptr<LoadingFiles> loadingFilesWeak = loadingFiles_;
    return CallbackConnection([loadingFilesWeak, loadingFileInfoIt] {
        auto loadingFiles = loadingFilesWeak.lock();
        if(loadingFiles) {
            loadingFiles->erase(loadingFileInfoIt);
        }
    });
}
