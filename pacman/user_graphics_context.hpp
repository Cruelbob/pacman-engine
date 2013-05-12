#pragma once

#include <memory>

#include <pacman_defs.hpp>
#include <user_image.hpp>

namespace pacman {
class user_graphics_context {
	user_graphics_context(const user_graphics_context& other);
	user_graphics_context& operator=(const user_graphics_context& other);
  protected:
	user_graphics_context() {}
  public:
	virtual ~user_graphics_context() {}

	virtual std::shared_ptr<user_image> create_image() = 0;
	virtual size_in_pixels_t get_screen_size() = 0;
};
}