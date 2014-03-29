#ifndef PACMAN_TEXTURE_FRAME_H
#define PACMAN_TEXTURE_FRAME_H

#include <cassert>

#include "Texture.h"

namespace pacman {
class TextureFrame {
  public:
    TextureFrame(const std::shared_ptr<Texture>& texture, const bounds2d& bounds, bool rotated = false):
      texture_(texture), bounds_(bounds), rotated_(rotated) { assert(texture); }

    TextureFrame(const std::shared_ptr<Texture>& texture):
        TextureFrame(texture, texture->getSize()) { assert(texture->isInitialized()); }

    void setTexture(const std::shared_ptr<Texture>& texture) { texture_ = texture; }
    const std::shared_ptr<Texture>& getTexture() const { return texture_; }
    void setBounds(const bounds2d& bounds) { bounds_ = bounds; }
    const bounds2d& getBounds() const { return bounds_; }
    void setRotated(bool rotated) { rotated_ = rotated; }
    bool getRotated() const { return rotated_; }

    bool isInitialized() const {
        return texture_->isInitialized();
    }
  private:
    std::shared_ptr<Texture> texture_;
    bounds2d bounds_;
    bool rotated_;
};
} // namespace pacman

#endif // PACMAN_TEXTURE_FRAME_H
