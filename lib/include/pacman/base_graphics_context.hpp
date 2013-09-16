#pragma once

#include "pacman_defs.hpp"
#include "image.hpp"

namespace pacman {
class game;
class base_graphics_context: public non_copyable {
  protected:
    virtual void render() = 0;

    friend class game;
};
} // namespace pacman
