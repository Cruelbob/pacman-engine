#include "sample_game_state.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <SDL.h>

void sample_game_state::initialize() {
    loading_image = get_graphics_context().create_image();
    
    SDL_Surface* surface = SDL_LoadBMP("loading_image.bmp");
    pacman::size_in_pixels_t image_size(surface->w,surface->h);
    std::vector<uint8_t> img_buffer((uint8_t*)surface->pixels,
                                    (uint8_t*)surface->pixels+image_size.area()*3);
    SDL_FreeSurface(surface);
    loading_image->load_from_buffer(img_buffer,
                                    pacman::image_buffer_format::raw_bgr,
                                    image_size);
    
    auto screen_size = get_graphics_context().get_screen_size();
    pacman::screen_point_t image_coords(screen_size.width/2-image_size.width/2,
                                        screen_size.height/2-image_size.height/2);
    loading_image->change_coords(image_coords);

    loading_image2 = get_graphics_context().create_image();
    
    surface = SDL_LoadBMP("loading_text.bmp");
    pacman::size_in_pixels_t image_size2(surface->w,surface->h);
    img_buffer.assign((uint8_t*)surface->pixels,
                      (uint8_t*)surface->pixels+image_size2.area()*3);
    SDL_FreeSurface(surface);
    
    loading_image2->load_from_buffer(img_buffer,
                                     pacman::image_buffer_format::raw_bgr,
                                     image_size2);
    pacman::screen_point_t image_coords2(screen_size.width/2-image_size2.width/2,
                                         image_coords.y + image_size.height);
    loading_image2->change_coords(image_coords2);
}

void sample_game_state::update(const pacman::time_type& delta) {
    float degrees = delta.count()/5;
    float radians = degrees/57;
    loading_image->set_rotation_angle(loading_image->get_rotation_angle()+radians); 
}