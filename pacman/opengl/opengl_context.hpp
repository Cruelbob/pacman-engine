#pragma once

#include <list>
#include <memory>

#include <pacman_defs.hpp>
#include <opengl/opengl_image.hpp>

namespace pacman {
class opengl_context {
    opengl_context(const opengl_context&);
    opengl_context& operator=(const opengl_context&);
  public:
    opengl_context();
    virtual ~opengl_context();

    void initialize(size_in_pixels_t screen_size);
    void render();
    void render_images();
    void render_image(const std::shared_ptr<opengl_image>& img);
    std::shared_ptr<user_image> create_image();
  private:
    uint32_t create_shader(std::string src,uint32_t type);

    size_in_pixels_t screen_size_;
    std::list<std::weak_ptr<opengl_image>> images_;
    uint32_t shader_program;
    int32_t attribute_coord2d,
            attribute_texcoord,
            uniform_texture,
            uniform_mvpmat;
};
}