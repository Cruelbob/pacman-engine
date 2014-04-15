#ifndef PACMAN_TEXTURE_H
#define PACMAN_TEXTURE_H

#include <cstdint>

#include "pacman/Config.h"

#if GL
#include <GL/gl.h>
#elif GLES2
#include <GLES2/gl2.h>
#endif


#include "array_view.h"
#include "Types.h"

namespace pacman {
class Texture {
  public:
    Texture()
#if GL || GLES2
      : texture_(0)
#endif
    {}

    ~Texture() { clear(); }

    Texture(const array_view<Color>& raw /* rgba8888 */, const size2d<uint32_t>& size);
    Texture(const array_view<Color>& raw /* rgba8888 */, uint32_t width, uint32_t height):
        Texture(raw, size2d<uint32_t>(width, height)) {}

#if EMSCRIPTEN
    void init(GLuint texture, const size2d<uint32_t>& size);
#endif
    void init(const array_view<Color>& raw /* rgba8888 */, const size2d<uint32_t>& size);
    void init(const array_view<Color>& raw /* rgba8888 */, uint32_t width, uint32_t height) {
        init(raw, size2d<uint32_t>(width, height));
    }

    bool isInitialized() const {
#if GL || GLES2
        return texture_ != 0;
#endif
    }

    size2d<uint32_t> getSize() const { return size_; }
    uint32_t getWidth() const { return size_.getWidth(); }
    uint32_t getHeight() const { return size_.getHeight(); }

    void clear();
  private:
    size2d<uint32_t> size_;
#if GL || GLES2
    GLuint texture_;
#endif
};
} // namespace pacman

#endif // PACMAN_TEXTURE_H
