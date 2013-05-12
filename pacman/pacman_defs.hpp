#pragma once

#include <cstdint>
#include <chrono>

namespace pacman { 
typedef uint16_t screen_coord_t;
typedef uint16_t pixels_number_t;
struct screen_point_t {
	screen_point_t(screen_coord_t x_ = 0,screen_coord_t y_ = 0): x(x_),y(y_) {}
    screen_coord_t x,
				  y;
};
struct size_in_pixels_t {
	size_in_pixels_t(pixels_number_t width_ = 0,pixels_number_t height_ = 0): 
	  width(width_),
	  height(height_) {}
	pixels_number_t width,
					height;
};

typedef std::chrono::duration<float, std::ratio<1,1000>> time_type;

enum class image_format {
    raw_rgb,
    raw_rgba,
    raw_bgr,
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

}