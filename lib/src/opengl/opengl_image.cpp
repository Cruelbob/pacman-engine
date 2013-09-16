#include <stdexcept>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "opengl_image.hpp"

namespace pacman {
opengl_image::opengl_image():
  texture_id(0) {
    glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_2D,texture_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
opengl_image::~opengl_image() {
    glDeleteTextures(1, &texture_id);
}

void opengl_image::load_raw_image(const std::vector<uint8_t>& buffer,image_buffer_format format,size2d size) {
    glBindTexture(GL_TEXTURE_2D,texture_id);
    GLenum gl_format;
    switch (format) {
      case image_buffer_format::raw_rgb:
        gl_format = GL_RGB;
        break;
      case image_buffer_format::raw_rgba:
        gl_format = GL_RGBA;
        break;
      case image_buffer_format::raw_bgr:
        gl_format = GL_BGR;
        break;
      default:
        throw std::runtime_error("image format error");
        break;
    }
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 size.width,
                 size.height,
                 0,
                 gl_format,
                 GL_UNSIGNED_BYTE,
                 buffer.data());
    size_ = size;
}

uint32_t opengl_image::get_texture_id() {
    return texture_id;
}
}
