#pragma once

#include <user_image.hpp>
#include <pacman_defs.hpp>

namespace pacman {
class opengl_image: public user_image {
    opengl_image(const opengl_image&);
    opengl_image& operator=(const opengl_image&);
  public:
    opengl_image();
    ~opengl_image() override;

    uint32_t get_texture_id();

    void load_from_buffer(const std::vector<uint8_t>& buffer,image_format format,size_in_pixels_t size = size_in_pixels_t()) override;
    void change_coords(screen_point_t coords) override;
    screen_point_t get_coords() override;
    size_in_pixels_t get_size() override;
    void set_rotation_angle(float angle) override;
    float get_rotation_angle() override;
  private:
    uint32_t texture_id;
    screen_point_t screen_position;
    size_in_pixels_t size_;
    float rotation_angle_;
};
}