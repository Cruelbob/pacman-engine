#include <cassert>
#ifdef GL
#include <GL/gl.h>
#endif

#include "pacman/GraphicsContext.h"

using namespace pacman;

GraphicsContext::GraphicsContext(): window_(nullptr), glContext_(nullptr) {
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    window_ = SDL_CreateWindow("",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640, 480,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    assert(window_);
    glContext_ = SDL_GL_CreateContext(window_);
    assert(glContext_);
}

GraphicsContext::~GraphicsContext() {
    SDL_GL_DeleteContext(glContext_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void GraphicsContext::update()
{
    SDL_GL_SwapWindow(window_);
}
