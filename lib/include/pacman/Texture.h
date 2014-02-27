#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>
#include "array_view.h"
#include "Color.h"
#include "Geometry.h"

namespace pacman {
class Texture {
  public:
    typedef size2d::size_type size_type;
    Texture(const array_view<Color>& raw /* rgba8888 */, const size2d& size);
    Texture(const array_view<Color>& raw /* rgba8888 */, size_type wdth, size_type height);

    void init(const array_view<Color>& raw /* rgba8888 */, const size2d& size);
    void init(const array_view<Color>& raw /* rgba8888 */, size_type wdth, size_type height);

    size_type getWidth() const { return width_; }
    size_type getHeight() const { return height_; }
  private:
    size_type width_;
    size_type height_;
};
} // namespace pacman

#endif // TEXTURE_H
