#include <cassert>

#include "pacman/GraphicsContext.h"

using namespace pacman;

GraphicsContext::GraphicsContext()
#if SDL == 1
    : screen_(nullptr)
#elif SDL == 2
    : window_(nullptr), glContext_(nullptr)
#endif
{
    int res = SDL_Init(SDL_INIT_VIDEO);
    assert(res == 0);
    (void)res;

#if SDL == 1
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );
    screen_ = SDL_SetVideoMode( 860, 640, 32, SDL_OPENGL );
    assert(screen_);
#elif SDL == 2
    window_ = SDL_CreateWindow("",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              860, 640,
                              SDL_WINDOW_OPENGL);
    assert(window_);
    glContext_ = SDL_GL_CreateContext(window_);
    assert(glContext_);
#endif
}

GraphicsContext::~GraphicsContext() {
#if SDL == 1
    SDL_FreeSurface(screen_);
#elif SDL == 2
    SDL_GL_DeleteContext(glContext_);
    SDL_DestroyWindow(window_);
#endif
    SDL_Quit();
}

void GraphicsContext::update()
{
#if SDL == 1
    SDL_GL_SwapBuffers();
#elif SDL == 2
    SDL_GL_SwapWindow(window_);
#endif
}
