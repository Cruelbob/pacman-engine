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

std::shared_ptr<Texture> GlobalTextureManager::getTexture(const std::string& name) {
    std::shared_ptr<Texture> texture(new Texture(), [this, name](Texture* texture) {
        textures_.erase(name);
        delete texture;
    });
    textures_.emplace(name, texture);
    game_.getGlobalFileManager().loadFile(name,
    [this](const std::string& filename, FileIO::LoadingStatus status, const array_view<uint8_t>& fileData) {
        callbacks.erase(filename);
        assert(status == FileIO::LoadingStatus::SUCCESS);
        std::vector<uint8_t> decoded;
        uint16_t width = 0, height = 0;
        assert(decode_png(fileData, decoded, width, height));
        auto textureWeakIt = textures_.find(filename);
        auto texture = textureWeakIt->second.lock();
        texture->init(decoded, width, height);
    });
    return texture;
}
