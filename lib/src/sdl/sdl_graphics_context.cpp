#include <cstdint>
#include <stdexcept>
#include <SDL.h>
#include <SDL_opengl.h>
#include <mathgl/mathgl.h>

#include "sdl_graphics_context.hpp"
#include <game.hpp>

namespace pacman {
std::shared_ptr<graphics_context> game::create_graphics_context() {
    return std::make_shared<sdl_graphics_context>();
}

sdl_graphics_context::sdl_graphics_context() {
    initialize_sdl();
    opengl_ctx.initialize(screen_size_);
}

sdl_graphics_context::~sdl_graphics_context() {
    SDL_Quit();
}

void sdl_graphics_context::render() {
    opengl_ctx.render();
    SDL_GL_SwapBuffers();
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch( event.type ) {
          case SDL_QUIT:
            throw std::runtime_error("Exit");
          case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                throw std::runtime_error("Exit");
            }
            break;
          default:
            break;
        }
    } 
}

size_in_pixels_t sdl_graphics_context::get_screen_size() {
    return screen_size_;
}

std::shared_ptr<user_image> sdl_graphics_context::create_image() {
    return opengl_ctx.create_image();
}

void sdl_graphics_context::initialize_sdl() {
    int err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    if(err != 0) {
        throw std::runtime_error(SDL_GetError());
    }
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    SDL_Surface *screen = nullptr;
    screen = SDL_SetVideoMode(0, 0,info->vfmt->BitsPerPixel, 
                              SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_OPENGL);
    if(!screen) {
        throw std::runtime_error(SDL_GetError());
    }
    screen_size_.width = screen->w;
    screen_size_.height = screen->h;
}
}
