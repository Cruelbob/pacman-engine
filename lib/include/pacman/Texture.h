#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>
#include "array_view.h"

namespace pacman {
class Texture {
  public:
    Texture();
    Texture(const array_view<uint8_t>& raw /* rgba8888 */, uint16_t wdth, uint16_t height);

    void init(const array_view<uint8_t>& raw /* rgba8888 */, uint16_t wdth, uint16_t height);

    bool isInitialized() const;

    uint16_t getWidth() const { return width_; }
    uint16_t getHeight() const { return height_; }
  private:
    uint16_t width_;
    uint16_t height_;
};
} // namespace pacman

#endif // TEXTURE_H
