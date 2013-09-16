#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <string>

#include "pacman_defs.hpp"

namespace pacman {
class image: public non_copyable {
  public:
    virtual ~image() {}

    /*virtual void load_from_stream(std::istream& input_stream,const image_format& format,size_in_pixels_t size = size_in_pixels_t()) = 0;
    virtual void load_from_file(std::string filename,image_format format = image_format::autoselect,size_in_pixels_t size = size_in_pixels_t());
    virtual bool set_visible(bool visible = true) = 0;
    virtual uint8_t set_z(uint8_t z) = 0;
    
    virtual float scale(float value) = 0;
    virtual size_in_pixels_t change_size(size_in_pixels_t size) = 0;
    */
    virtual void load_raw_image(const std::vector<uint8_t>& buffer, image_buffer_format format, size2d size) = 0;
    void load_raw_image(const std::vector<uint8_t> &buffer, image_buffer_format format, uint16_t width, uint16_t height) {
        return load_raw_image(buffer,format,size2d(width,height));
    }

    void change_coords(screen_point_t coords) {
        coords_ = coords;
    }
    screen_point_t get_coords() const {
        return coords_;
    }
    size2d get_size() const {
        return size_;
    }
    void set_rotation_angle(float angle) {
        angle_ = angle;
    }

    float get_rotation_angle() const {
        return angle_;
    }

    //virtual bool has_image() = 0;
  protected:
    image(): coords_(0,0), size_(0,0), angle_(0.f)  {}

    screen_point_t coords_;
    size2d size_;
    float angle_;
};
} // namespace pacman
