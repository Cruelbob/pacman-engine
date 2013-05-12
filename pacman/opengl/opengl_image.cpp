#include <opengl/opengl_image.hpp>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace pacman {
opengl_image::opengl_image():
  texture_id(0),
  screen_position(0,0),
  size_(0,0),
  rotation_angle_(0.f) {
    glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_2D,texture_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
opengl_image::~opengl_image() {
    glDeleteTextures(1, &texture_id);
}

void opengl_image::load_from_buffer(const std::vector<uint8_t>& buffer,const image_format& format,size_in_pixels_t size) {
    glBindTexture(GL_TEXTURE_2D,texture_id);
    GLenum gl_format;
    switch (format) {
      case image_format::raw_rgb:
        gl_format = GL_RGB;
        break;
      case image_format::raw_rgba:
        gl_format = GL_RGBA;
        break;
      case image_format::raw_bgr:
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

void opengl_image::change_coords( screen_point_t coords )
{
    screen_position = coords;
}

screen_point_t opengl_image::get_coords() {
    return screen_position;
}

size_in_pixels_t opengl_image::get_size() {
    return size_;
}

void opengl_image::set_rotation_angle(float angle) {
    rotation_angle_ = angle;
}

float opengl_image::get_rotation_angle() {
    return rotation_angle_;
}

uint32_t opengl_image::get_texture_id() {
    return texture_id;
}
}