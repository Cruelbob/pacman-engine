#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"

namespace pacman {
namespace Graphics {
class Sprite {
  public:
    Sprite() {}
    Sprite(const std::shared_ptr<Texture>& texture):
        texture_(texture), textureBounds_(0,0,texture->getWidth(),texture->getHeight()) {}
    Sprite(const std::shared_ptr<Texture>& texture, const bounds2d& bounds):
        texture_(texture), textureBounds_(bounds) {}
    Sprite(const Sprite& otherSprite, const bounds2d& bounds):
        texture_(otherSprite.texture_),
        textureBounds_(otherSprite.textureBounds_.getAbsoluteBounds(bounds)) {}

    bool isInitialized() const {
        return texture_ != nullptr;
    }
  private:
    std::shared_ptr<Texture> texture_;
    bounds2d textureBounds_;
};
} // namespace Graphics
} // namespace pacman

#endif // SPRITE_H
