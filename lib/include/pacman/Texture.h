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
    typedef float size_type;
    Texture()
#if GL || GLES2
      : texture_(0)
#endif
    {}

    ~Texture() { clear(); }

    Texture(const array_view<Color>& raw /* rgba8888 */, const size2d& size);
    Texture(const array_view<Color>& raw /* rgba8888 */, size_type width, size_type height):
        Texture(raw, size2d(width, height)) {}

#if EMSCRIPTEN
    void init(GLuint texture, const size2d& size);
#endif
    void init(const array_view<Color>& raw /* rgba8888 */, const size2d& size);
    void init(const array_view<Color>& raw /* rgba8888 */, size_type width, size_type height) {
        init(raw, size2d(width, height));
    }

    bool isInitialized() const {
#if GL || GLES2
        return texture_ != 0;
#endif
    }

    size2d getSize() const { return size_; }
    size_type getWidth() const { return size_.getWidth(); }
    size_type getHeight() const { return size_.getHeight(); }

    void clear();
  private:
    size2d size_;
#if GL || GLES2
    GLuint texture_;
#endif
};
} // namespace pacman

#endif // PACMAN_TEXTURE_H
