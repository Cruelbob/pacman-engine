#include "pacman/Atlas.h"

using namespace pacman;

TextureFrame TextureAtlas::getFrame(const std::string &name) const {
    auto frameIt = sprites_.find(name);
    if(frameIt != sprites_.end()) {
        return TextureFrame(texture_, frameIt->second);
    } else {
        return TextureFrame(texture_);
    }
}
