#pragma once

#include <list>
#include <memory>

#include <pacman/pacman_defs.hpp>
#include "opengl_image.hpp"

namespace pacman {
class opengl_context: public non_copyable {
  public:
    opengl_context();
    virtual ~opengl_context();

    void initialize(size2d screen_size);
    void render();
    void render_images();
    void render_image(const std::shared_ptr<opengl_image>& img);
    std::shared_ptr<image> create_image();
  private:
    uint32_t create_shader(std::string src,uint32_t type);

    size2d screen_size_;
    std::list<std::weak_ptr<opengl_image>> images_;
    uint32_t shader_program;
    int32_t attribute_coord2d,
            attribute_texcoord,
            uniform_texture,
            uniform_mvpmat;
};
}
