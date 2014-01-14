#include <vector>
#include <cstdint>
#include <functional>
#include <cassert>

#include "pacman/GlobalTextureManager.h"
#include "pacman/array_view.h"
#include "pacman/Texture.h"
#include "pacman/FileManager.h"
#include "pacman/Game.h"
#include "pacman/GameScene.h"

using namespace pacman;

bool decode_png(const array_view<uint8_t>& encoded,
                std::vector<uint8_t>& decodedOut,
                uint16_t& widthOut,
                uint16_t& heightOut);

void GlobalTextureManager::onTextureLoad(const std::weak_ptr<Texture>& textureWeak,
                                         const FileManager::LoadingFile& loadingFile)
{
    auto texture = textureWeak.lock();
    if(texture) {
        assert(loadingFile.getStatus() != FileManager::LoadingStatus::FAILURE);
        if(loadingFile.getStatus() == FileManager::LoadingStatus::SUCCESS) {
            std::vector<uint8_t> decoded;
            uint16_t width;
            uint16_t height;
            assert(decode_png(loadingFile.getBufferView(), decoded, width, height));
            texture->init(decoded, width, height);
        } else if(loadingFile.getStatus() == FileManager::LoadingStatus::CANCELED) {
            // TODO: dont load texture from beginning
            FileManager& fileManeger = game_.getCurrentGameScene().getFileManager();
            fileManeger.loadFile(loadingFile.getFilename(),
                                 [this, textureWeak](const FileManager::LoadingFile& loadingFile)
            {
                onTextureLoad(textureWeak, loadingFile);
            });
        }
    }
}

std::shared_ptr<Texture> GlobalTextureManager::getTexture(const std::string& name) {
    auto texture = std::make_shared<Texture>();
    textures_.emplace(name,texture);
    std::weak_ptr<Texture> textureWeak = texture;
    FileManager& fileManeger = game_.getCurrentGameScene().getFileManager();
    fileManeger.loadFile(name,
                         [this, textureWeak](const FileManager::LoadingFile& loadingFile)
    {
        onTextureLoad(textureWeak, loadingFile);
    });
    return texture;
}
