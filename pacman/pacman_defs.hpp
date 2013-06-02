#pragma once

#include <cstdint>
#include <chrono>

namespace pacman { 
typedef uint16_t screen_coord_t;
typedef uint16_t pixels_number_t;
typedef uint32_t area_in_pixels;
struct screen_point_t {
	screen_point_t(screen_coord_t x_ = 0,screen_coord_t y_ = 0): x(x_),y(y_) {}
    screen_coord_t x,
				  y;
};
struct size_in_pixels_t {
	size_in_pixels_t(pixels_number_t width_ = 0,pixels_number_t height_ = 0): 
	  width(width_),
	  height(height_) {}
    area_in_pixels area() {
        return area_in_pixels(width)*height;
    }
	pixels_number_t width,
					height;
};

typedef std::chrono::duration<float,std::milli> time_type;

enum class image_buffer_format {
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