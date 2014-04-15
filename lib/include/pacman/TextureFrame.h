#ifndef PACMAN_TEXTURE_FRAME_H
#define PACMAN_TEXTURE_FRAME_H

#include <cassert>

#include "Texture.h"

namespace pacman {
class TextureFrame {
  public:
    TextureFrame(const std::shared_ptr<Texture>& texture, const Frame& info):
      texture_(texture), frame_(info) { assert(texture); }

    TextureFrame(const std::shared_ptr<Texture>& texture):
        TextureFrame(texture, bounds2d<float>(0.0f, 0.0f, 1.0f, 1.0f)) {}

    const std::shared_ptr<Texture>& getTexture() const { return texture_; }
    const Frame& getFrame() const { return frame_; }
    size2d<uint32_t> getSizeInPoints() const {
        assert(texture_ && texture_->isInitialized());
        size2d<uint32_t> textureSize = texture_->getSize();
        size2d<float> frameSize = frame_.getBounds().getSize();
        uint32_t width = textureSize.getWidth() * frameSize.getWidth();
        uint32_t height = textureSize.getHeight() * frameSize.getHeight();
        return frame_.isRotated() ? size2d<uint32_t>(height, width) : size2d<uint32_t>(width, height);
    }
  private:
    std::shared_ptr<Texture> texture_;
    Frame frame_;

};
} // namespace pacman

#endif // PACMAN_TEXTURE_FRAME_H
