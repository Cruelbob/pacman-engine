#include "pacman/Atlas.h"

using namespace pacman;

TextureFrame TextureAtlas::getFrame(const std::string &name) const {
    auto regionIt = sprites_.find(name);
    if(regionIt != sprites_.end()) {
        return TextureFrame(texture_, regionIt->second.bounds, regionIt->second.rotated);
    } else {
        return TextureFrame(texture_);
    }
}
