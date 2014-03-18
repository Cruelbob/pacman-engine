#include "pacman/Atlas.h"

using namespace pacman;
using namespace pacman::Graphics;


Sprite Atlas::getSprite(const std::string &name) const {
    auto regionIt = sprites_.find(name);
    if(regionIt != sprites_.end()) {
        return Sprite(texture_, regionIt->second);
    } else {
        return Sprite();
    }
}
