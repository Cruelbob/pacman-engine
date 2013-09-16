#pragma once

#include <pacman/image.hpp>
#include <pacman/pacman_defs.hpp>

namespace pacman {
class opengl_image: public image {
  public:
    opengl_image();
    ~opengl_image() override;

    uint32_t get_texture_id();

    void load_raw_image(const std::vector<uint8_t>& buffer,image_buffer_format format,size2d size = size2d()) override;
  private:
    uint32_t texture_id;
};
}
