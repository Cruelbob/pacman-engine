#include "pacman/Texture.h"

using namespace pacman;
using namespace pacman::Graphics;

GLuint makeTexture(const array_view<Color> &raw, const size2d &size) {
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

Texture::Texture(const array_view<Color> &raw, const size2d &size):
    size_(size), texture_(makeTexture(raw, size)) {}

void Texture::init(const array_view<Color> &raw, const size2d &size) {
    size_ = size;
    texture_ = makeTexture(raw, size);
}
