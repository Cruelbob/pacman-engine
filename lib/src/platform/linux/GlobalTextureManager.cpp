#include <vector>
#include <cstdint>
#include <functional>
#include <cassert>

#include "pacman/GlobalTextureManager.h"
#include "pacman/Texture.h"
#include "pacman/Game.h"
#include "pacman/GlobalFileManager.h"

using namespace pacman;
using namespace pacman::Graphics;
using namespace pacman::FileIO;

bool decode_png(const array_view<uint8_t>& encoded,
                std::vector<uint8_t>& decodedOut,
                uint16_t& widthOut,
                uint16_t& heightOut);

std::shared_ptr<Texture> GlobalTextureManager::getTexture(const std::string &name) {
    std::shared_ptr<Texture> texture;
    auto texturIt = textures_.find(name);
    if(texturIt != textures_.end()) {
        texture = texturIt->lock();
    } else {
        texture = std::make_shared<Texture>();
        auto infoIt = game_.getGlobalFileManager().loadFile(name,
        [this](const std::string& filename, LoadingStatus status, const array_view<uint8_t>& fileData) {
            loadingCallbacks_.erase(filename);
            assert(status != FileIO::LoadingStatus::FAILURE);

//            std::vector<uint8_t> decoded;
//            uint16_t width = 0, height = 0;
//            assert(decode_png(fileData, decoded, width, height));
//            auto textureWeakIt = textures_.find(filename);
//            auto texture = textureWeakIt->second.lock();
//            texture->init(decoded, width, height);
        });
    }

    return texture;
}
