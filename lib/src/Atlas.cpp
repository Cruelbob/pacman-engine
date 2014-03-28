#include "pacman/Atlas.h"

using namespace pacman;
using namespace pacman::Graphics;

bounds2d Atlas::getSpriteBounds(const std::string &name) const {
    auto regionIt = sprites_.find(name);
    if(regionIt != sprites_.end()) {
        return regionIt->second;
    } else {
        return bounds2d();
    }
}
