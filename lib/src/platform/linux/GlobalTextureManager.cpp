#include <vector>
#include <cstdint>
#include <functional>
#include <cassert>

#include <png.h>

#include "pacman/GlobalTextureManager.h"
#include "pacman/Texture.h"
#include "pacman/Game.h"
#include "pacman/GlobalFileManager.h"

using namespace pacman;

bool decode_png(const array_view<uint8_t>& encoded, std::vector<Color>& decodedOut, size2d<uint32_t>& sizeOut) {
    png_image image;
    memset(&image, 0, sizeof(png_image));
    image.version = PNG_IMAGE_VERSION;
    if(!png_image_begin_read_from_memory(&image, encoded.data(), encoded.size())) {
        return false;
    }

    sizeOut.set(image.width, image.height);
    decodedOut.resize(sizeOut.getWidth() * sizeOut.getHeight());
    image.format = PNG_FORMAT_RGBA;
    if(!png_image_finish_read(&image, nullptr, decodedOut.data(), 0, 0)) {
        return false;
    }

    return true;
}

bool decode_image(const array_view<uint8_t>& encoded, std::vector<Color>& decodedOut, size2d<uint32_t>& sizeOut) {
    if(!png_sig_cmp(encoded.data(), 0, 8)) {
        return decode_png(encoded, decodedOut, sizeOut);
    }
    return false;
}

std::shared_ptr<Texture> GlobalTextureManager::getTexture(const std::string &name) {
    std::shared_ptr<Texture> texture;
    auto texturIt = textures_.find(name);
    if(texturIt != textures_.end()) {
        texture = texturIt->second.lock();
    } else {
        texture.reset(new Texture(), [this, name](Texture* texture) {
            textures_.erase(name);
            loadingCallbacks_.erase(name);
            delete texture;
        });
        textures_.emplace(name, texture);
        auto connection = game_.getGlobalFileManager().loadFile(name,
        [this](const std::string& filename, LoadingStatus status, const array_view<uint8_t>& fileData) {
            loadingCallbacks_.erase(filename);
            assert(status != LoadingStatus::FAILURE);
            auto textureIt = textures_.find(filename);
            if(status == LoadingStatus::SUCCESS) {
                std::vector<Color> decodedImage;
                size2d<uint32_t> imageSize;
                bool isDecoded = decode_image(fileData, decodedImage, imageSize);
                assert(isDecoded);
                std::shared_ptr<Texture> texture = textureIt->second.lock();
                if(texture && !texture->isInitialized()) {
                    texture->init(decodedImage, imageSize);
                }
            }
        });
        loadingCallbacks_.emplace(name, std::move(connection));
    }

    return texture;
}
