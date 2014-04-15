#include "pacman/Texture.h"

using namespace pacman;

GLuint makeTexture(const array_view<Color> &raw, const size2d<uint32_t> &size) {
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 size.getWidth(), size.getHeight(),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE, raw.data());
    return texture;
}

Texture::Texture(const array_view<Color> &raw, const size2d<uint32_t> &size):
    size_(size), texture_(makeTexture(raw, size)) {}

#if EMSCRIPTEN
void Texture::init(GLuint texture, const size2d<uint32_t> &size) {
    clear();
    texture_ = texture;
    size_ = size;
}
#endif

void Texture::init(const array_view<Color> &raw, const size2d<uint32_t> &size) {
    clear();
    size_ = size;
    texture_ = makeTexture(raw, size);
}

void Texture::clear() {
    if(isInitialized()) {
        glDeleteTextures(1, &texture_);
        texture_ = 0;
        size_.set(0, 0);
    }
}
