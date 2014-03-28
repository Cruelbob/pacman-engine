#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "Node.h"

namespace pacman {
class GameScene;
namespace Graphics {
class Sprite: public Node {
  public:
    Sprite(const std::shared_ptr<Texture>& texture, const bounds2d& bounds, bool rotated = false):
      texture_(texture), textureBounds_(bounds), boundsInitialized_(true), rotated_(rotated) {}

    Sprite(const std::shared_ptr<Texture>& texture):
      Sprite(texture, bounds2d(0, 0, texture->getWidth(), texture->getHeight())) { assert(texture); }

    Sprite(): boundsInitialized_(false), rotated_(false) {}

    Sprite(const Sprite& other, const bounds2d& bounds, bool rotated = false):
      Sprite(other.texture_, other.textureBounds_.getAbsoluteBounds(bounds), rotated) {}

    bool isInitialized() const {
        return texture_ != nullptr && boundsInitialized_ && texture_->isInitialized();
    }

    void update(Time deltaTime) override;
    void draw() override;
  private:
    std::shared_ptr<Texture> texture_;
    bounds2d textureBounds_;
    bool boundsInitialized_;
    bool rotated_;
};
} // namespace Graphics
} // namespace pacman

#endif // SPRITE_H
