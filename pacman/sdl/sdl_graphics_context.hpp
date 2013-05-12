#pragma once

#include <memory>
#include <list>
#include <string>

#include <graphics_context.hpp>
#include <opengl/opengl_context.hpp>

namespace pacman {
class sdl_graphics_context: public graphics_context {
    sdl_graphics_context(const sdl_graphics_context&);
    sdl_graphics_context& operator=(const sdl_graphics_context&);
  public:
    sdl_graphics_context();
    ~sdl_graphics_context() override;

    std::shared_ptr<user_image> create_image() override;
    size_in_pixels_t get_screen_size() override;
    void render() override;
  private:
    void initialize_sdl();

    size_in_pixels_t screen_size_;
    opengl_context opengl_ctx;
};
}