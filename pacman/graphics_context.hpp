#pragma once

#include <user_graphics_context.hpp>

namespace pacman {
class graphics_context: public user_graphics_context {
    graphics_context(const graphics_context&);
    graphics_context& operator=(const graphics_context&);
  public:
    graphics_context() {}

    virtual void render() = 0;
};
} // namespace pacman
