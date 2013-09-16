#pragma once

#include <memory>

#include "base_graphics_context.hpp"

namespace pacman {
class graphics_context: public base_graphics_context {
  public:
    virtual std::shared_ptr<image> create_image() = 0;
    size2d get_screen_size() const {
        return screen_size_;
    }
  protected:
    size2d screen_size_;
};
} // namespace pacman
