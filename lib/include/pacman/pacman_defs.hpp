#pragma once

#include <cstdint>
#include <chrono>

namespace pacman { 
typedef uint16_t screen_coord_t;
typedef uint32_t area_in_pixels;
struct screen_point_t {
    screen_point_t(screen_coord_t x_ = 0,screen_coord_t y_ = 0): x(x_),y(y_) {}
    screen_coord_t x,
                  y;
};
struct size2d {
    size2d(uint16_t width_ = 0,uint16_t height_ = 0):
      width(width_),
      height(height_) {}
    uint32_t area() const {
        return uint32_t(width)*height;
    }
    uint16_t width,
             height;
};

typedef std::chrono::duration<double,std::milli> time_type;

enum class image_buffer_format {
    raw_rgb,
    raw_rgba,
    raw_bgr,
};

class non_copyable
{
  protected:
    non_copyable() {}
    virtual ~non_copyable() {}
  private:
    non_copyable(const non_copyable&);
    non_copyable& operator=(const non_copyable&);
};

struct input_event_t {
#ifdef _WIN32
    /*enum class types {
        mouse_click,
        key_down
    } type;
    union {
        screen_point_t coords;
        enum class keys {
            up,
            down,
            right,
            left
        } key;
    } info;*/
#endif // _WIN32
};

} // namespace pacman
