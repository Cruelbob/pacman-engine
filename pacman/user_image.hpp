#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

#include <pacman_defs.hpp>

namespace pacman {
class user_image {
    user_image(const user_image& other);
    user_image& operator=(const user_image& other);
  protected:
    user_image() {}
  public:
    virtual ~user_image() {}

    /*virtual void load_from_stream(std::istream& input_stream,const image_format& format,size_in_pixels_t size = size_in_pixels_t()) = 0;
    virtual void load_from_file(std::string filename,image_format format = image_format::autoselect,size_in_pixels_t size = size_in_pixels_t());
    virtual bool set_visible(bool visible = true) = 0;
    virtual uint8_t set_z(uint8_t z) = 0;
    
    virtual float scale(float value) = 0;
    virtual size_in_pixels_t change_size(size_in_pixels_t size) = 0;
    */
    virtual void load_from_buffer(const std::vector<uint8_t>& buffer,image_buffer_format format,size_in_pixels_t size = size_in_pixels_t()) = 0;
    virtual void change_coords(screen_point_t coords) = 0;
    virtual screen_point_t get_coords() = 0;
    virtual size_in_pixels_t get_size() = 0;
    virtual void set_rotation_angle(float angle) = 0;
    virtual float get_rotation_angle() = 0;
    //virtual bool has_image() = 0;
};
} // namespace pacman
