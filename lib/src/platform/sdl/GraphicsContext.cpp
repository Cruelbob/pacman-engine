#include <cassert>

#if GLES2
#include <GLES2/gl2.h>
#endif

#include "pacman/GraphicsContext.h"

using namespace pacman;

GraphicsContext::GraphicsContext(): screen_(nullptr) {
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    screen_ = SDL_SetVideoMode( 640, 480, 32, SDL_OPENGL );
    assert(screen_);
}

GraphicsContext::~GraphicsContext() {
    SDL_FreeSurface(screen_);
    SDL_Quit();
}

void GraphicsContext::update()
{
    SDL_GL_SwapBuffers();
}
