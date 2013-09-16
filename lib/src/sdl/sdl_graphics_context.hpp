#pragma once

#include <memory>
#include <list>
#include <string>

#include <pacman/graphics_context.hpp>
#include "../opengl/opengl_context.hpp"

namespace pacman {
class sdl_graphics_context: public graphics_context {
    sdl_graphics_context(const sdl_graphics_context&);
    sdl_graphics_context& operator=(const sdl_graphics_context&);
  public:
    sdl_graphics_context();
    ~sdl_graphics_context() override;

    std::shared_ptr<image> create_image() override;
    void render() override;
  private:
    void initialize_sdl();

    opengl_context opengl_ctx;
};
}
